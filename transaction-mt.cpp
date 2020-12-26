#include "transaction-mt.hpp"

namespace transaction_mt {
    using tsv_type = uint64_t; // Timestamp value
    using tx_id_type = uint64_t; // Transaction id
    using item_id_type = uint64_t; // Item id

    class lockable_item;

    class transaction_manager {
    public:
        ~transaction_manager();
        transaction_manager(int log_level, FILE *P = nullptr);

        tx_id_type id() const noexcept;
        tsv_type   tsv() const noexcept;

        void begin();
        void commit();
        void rollback();

        bool acquire(lockable_item& item);
    private:
        using item_ptr_list = std::vector<lockable_item*>;
        using mutex         = std::mutex;
        using tx_lock       = std::unique_lock<std::mutex>;
        using cond_var      = std::condition_variable;
        using atomic_tsv    = std::atomic<tsv_type>;
        using atomic_tx_id  = std::atomic<tx_id_type>;

        tx_id_type      m_tx_id;
        tsv_type        m_tx_tsv;
        item_ptr_list   m_item_ptrs;
        mutex           m_mutex;
        cond_var        m_cond;
        FILE          * m_fp;
        int             m_log_level;

        static atomic_tsv   sm_tsv_generator;
        static atomic_tx_id sm_tx_id_generator;
        void log_begin() const;
        void log_commit() const;
        void log_rollback() const;
        void log_acquisition_success(const lockable_item & item) const;
        void log_acquisition_failure(const lockable_item &  item) const;
        void log_acquisition_same(const lockable_item & item) const;
        void log_acquisition_waiting(lockable_item & item, transaction_manager * p_curr_tx) const;
    };

    transaction_manager::atomic_tsv transaction_manager::sm_tsv_generator = 0;
    transaction_manager::atomic_tx_id transaction_manager::sm_tx_id_generator = 0;

    transaction_manager::transaction_manager(int log_level, FILE* fp) :
    m_tx_id(++sm_tx_id_generator),
    m_tx_tsv(0),
    m_item_ptrs(),
    m_mutex(),
    m_cond(),
    m_fp(fp),
    m_log_level(log_level)
    {
        m_item_ptrs.reserve(100u);
    }

    inline tx_id_type
    transaction_manager::id() const noexcept
    {
        return m_tx_id;
    }

    inline tsv_type
    transaction_manager::tsv() const noexcept
    {
        return m_tx_tsv;
    }

    void
    transaction_manager::begin() {
        m_mutex.lock();
        m_tx_tsv = ++sm_tsv_generator;
        m_mutex.unlock();
    }

    void
    transaction_manager::commit()
    {
        tx_lock lock(m_mutex);

        while(m_item_ptrs.size() != 0)
        {
            m_item_ptrs.back()->mp_owning_tx.store(nullptr);
            m_item_ptrs.pop_back();
        }
        m_cond.notify_all();
    }

    bool transaction_manager::acquire(lockable_item &item) {
        while(true)
        {
            transaction_manager * p_curr_tx = nullptr;
            if (item.mp_owning_tx.compare_exchange_strong(p_curr_tx, this))
            {
                m_item_ptrs.push_back(&item);

                if (m_tx_tsv > item.last_tsv())
                {
                    item.m_last_tsv = m_tx_tsv;
                    return true;
                } else
                {
                    return false;
                }
            }
            else {
                if (p_curr_tx == this) {
                    return true;
                } else {
                    tx_lock lock(p_curr_tx->m_mutex);
                    while(item.mp_owning_tx.load() == p_curr_tx)
                    {
                        if(p_curr_tx->m_tx_tsv > m_tx_tsv)
                        {
                            return false;
                        }
                        p_curr_tx->m_cond.wait(lock);
                    }
                }
            }
        }
    }

    class lockable_item
    {
    public:
        lockable_item();

        item_id_type id() const noexcept;
        tsv_type last_tsv() const noexcept;
    private:
        friend class transaction_manager;

        using atomic_txm_pointer = std::atomic<transaction_manager*>;
        using atomic_item_id = std::atomic<item_id_type>;

        atomic_txm_pointer mp_owning_tx; // Pointer to transaction manager
        tsv_type           m_last_tsv;   // Timestamp of last owner
        item_id_type       m_item_id;    // For debugging/tracking/logging

        static atomic_item_id sm_item_id_generator;
    };

    inline
    lockable_item::lockable_item() : mp_owning_tx(nullptr),m_last_tsv(0),m_item_id(sm_item_id_generator++)
    {}

    inline item_id_type
    lockable_item::id() const noexcept
    {
        return m_item_id;
    }

    inline tsv_type
    lockable_item::last_tsv() const noexcept
    {
        return m_last_tsv;
    }
    lockable_item::atomic_item_id lockable_item::sm_item_id_generator = 0;
    class stopwatch;
}
