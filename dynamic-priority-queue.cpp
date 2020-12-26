#include <vector>
#include <iostream>
#include <algorithm>

namespace dynamic_pq {

    struct key_value {
        key_value(const int key, const int value);

        int key;
        int value;

        void swap(key_value &rhs);

        key_value &operator=(const key_value &rhs);

        friend std::ostream &operator<<(std::ostream &os, const key_value &kv);
    };

    key_value::key_value(const int key, const int value) : key(key), value(value) {}

    void key_value::swap(key_value &rhs) {
        std::swap(this->key, rhs.key);
        std::swap(this->value, rhs.value);
    }

    key_value &key_value::operator=(const key_value &rhs) {
        if (this != &rhs) {
            this->key = rhs.key;
            this->value = rhs.value;
        }
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const key_value &kv) {
        os << "key: " << kv.key << " value: " << kv.value << "\n";
        return os;
    }

    class comparison {
    public:
        bool operator()(const key_value &lhs, const key_value &rhs);
    };

    bool comparison::operator()(const dynamic_pq::key_value &lhs, const dynamic_pq::key_value &rhs) {
        return lhs.value < rhs.value;
    }

    template <class T, class comp>
    class dynamic_pq;

    template <class T, class comp>
    std::ostream & operator <<(std::ostream &os, const dynamic_pq<T,comp> &q);

    template<class T, class comp = std::less<T>>
    class dynamic_pq {
    public:
        dynamic_pq();

        void insert(const T &elm);

        friend std::ostream &operator<< <> (std::ostream &os, const dynamic_pq &q);

    private:
        std::vector<T> pq;

        void sink(const int index);

        void swim(int index);

        void swap(int parent, int child);

        void clear(const int index);

        void remove(const int ki);

        T extract_min();

        std::vector<int> val;
        std::vector<int> pm; // Position map to map from key index to node position
        std::vector<int> im; // Inverse map to map from node position to key index
        comp comparison;
    };

    typedef ::dynamic_pq::dynamic_pq<::dynamic_pq::key_value, ::dynamic_pq::comparison> dynq;
    typedef ::dynamic_pq::key_value kv;

    template <class T, class comp>
    std::ostream & operator <<(std::ostream &os, const dynq &q) {
        std::for_each(q.pq.begin(), q.pq.end(), [&](const T &elm) {
            os << *elm << std::endl;
        });
        return os;
    }

    template<class T, class comp>
    dynamic_pq<T, comp>::dynamic_pq() {}

    template<class T, class comp>
    void dynamic_pq<T, comp>::swap(int parent, int child) {

        //pm[pq[parent].key] = child;
        pm[im[parent]] = child;
        pm[im[child]] = parent;

        int tmp = im[parent];
        im[parent] = im[child];
        im[child] = tmp;
        pq[parent].swap(pq[child]);
    }

    template<class T, class comp>
    void dynamic_pq<T, comp>::swim(int index) {
        // Compare index value with parent.
        for (int i = (index - 1) / 2; i >= 0 && comparison(pq[index], pq[i]); index = i, i = (index - 1) / 2) {
            swap(index, i);
        }
    }

    template<class T, class comp>
    void dynamic_pq<T, comp>::insert(const T &elm) {
        pq.push_back(elm);
        val.push_back(elm.value);
        pm.push_back(pq.size() - 1);
        im.push_back(elm.key);
        swim(pq.size() - 1);
    }

    template<class T, class comp>
    void dynamic_pq<T, comp>::clear(const int index) {
        val[im[index]] = -1;
        pm[im[index]] = -1;
        im[index] = -1;
    }

    template<class T, class comp>
    void dynamic_pq<T, comp>::sink(const int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < pq.size() && pq[left] < pq[smallest]) {
            smallest = left;
        }

        if (right < pq.size() && pq[right] < pq[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            pq[index].swap(pq[smallest]);
            sink(smallest);
        }
    }

    template<class T, class comp>
    T dynamic_pq<T, comp>::extract_min() {
        if (!pq.empty()) {
            T top = pq.front();
            if (pq.size() > 1) {
                swap(0, pq.size() - 1);
                pq.clear(pq.size() - 1);
                pq.pop_back();
                sink(0);
            } else {
                pq.clear(pq.size() - 1);
                pq.pop_back();
            }
        }
    }

    template<class T, class comp>
    void dynamic_pq<T, comp>::remove(const int ki) {
        int i = pm[ki];
        swap(i, pq.size() - 1);
        sink(i);
        swim(i);
        val[ki] = -1;
        pm[ki] = -1;
        im[pq.size() - 1] = -1;
    }

    typedef ::dynamic_pq::kv kv;

    int main() {
        ::dynamic_pq::dynq q;
        q.insert(::dynamic_pq::kv(0, 1));
        q.insert(kv(1, 3));
        q.insert(kv(2, 5));
        q.insert(kv(3, 8));
        q.insert(kv(4, 2));
        q.insert(kv(5, 4));

//    std::cout << q << std::endl;
    }

}





