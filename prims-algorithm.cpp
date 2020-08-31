#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <list>
#include <iostream>

namespace min_heap {
    struct node {
        std::string name;

        node &operator=( node &  rhs )
        {
            if ( this != &rhs )
            {
                this->name = rhs.name;
                return *this;
            }
        }
        bool operator<( node & rhs )
        {
            return this->name < rhs.name;
        }
    };

    template<class T>
    class min_heap {
    public:
        min_heap(int capacity);

        bool contains(T &data) const;   /// O ( 1 )
        void decrease_key(int index, T val);              /// O ( log n )
        void insert(T e);             /// O ( log n )
        T extract_min();
        void delete_key( int index );
        int parent(int index) const { return index - 1 / 2; }

        void swap(T &parent, T &child) {
            T temp = parent;
            parent = child;
            child = parent;
        }

        void min_heapify(int index);
        int left(int index) { return 2 * index + 1; }
        int right(int index) { return 2 * index + 2; }
        int get_min() const { return adj[0]; }
    private:
        std::vector<T> adj;
        int capacity_;
        int heap_size_;
    };

    template <class T>
    min_heap<T>::
    min_heap(int capacity) :
            capacity_(capacity),
            heap_size_(0) {
        adj.resize(capacity);
    }

    template <class T>
    void
    min_heap<T>::
    insert(T e) {
        if (heap_size_ == capacity_) {
            std::cout << "Overflow: could not insert key" << std::endl;
            return;
        }
        heap_size_++;
        int i = heap_size_ - 1;
        adj[i] = e;
        while (i != 0 && adj[parent(i)] > adj[i]) {
            swap(adj[parent(i)], adj[i]);
            i = parent(i);
        }
    }

    template <class T>
    void
    min_heap<T>::
    decrease_key(int index, T val) {
        adj[index] = val;
        while (index != 0 && adj[parent(index)] > adj[index]) {
            swap(adj[parent(index)], adj[index]);
            index = parent(index);
        }
    }

    template  <class T>
    T return_max( typename std::enable_if<std::is_same<T,int>::value>::type * = 0 )
    {
        return INT_MAX;
    }

    template <class T>
    T return_max( typename std::enable_if<std::is_same<T, node>::value>::type * = 0 )
    {

    }
    template<class T>
    T min_heap<T>::extract_min() {
        if (heap_size_ <= 0)
            return_max<T>();
        if (heap_size_ == 1) {
            heap_size_--;
            return adj[0];
        }

        T root = adj[0];
        adj[0] = adj[heap_size_-1];
        heap_size_--;
        min_heapify(0);
        return root;
    }

    template<class T>
    void min_heap<T>::min_heapify(int index) {
        int l = left(index);
        int r = right(index);
        int smallest = index;
        if (l < heap_size_ && adj[l] < adj[smallest])
            smallest = l;
        if (r < heap_size_ && adj[r] < adj[smallest])
            smallest = r;
        if (smallest != index) {
            swap(adj[index], adj[smallest]);
            min_heapify( smallest );
        }
    }

    template <class T>
    void min_heap<T>::delete_key(int index) {
        decrease_key( index, INT_MIN );
        extract_min();
    }
    int main()
    {
        min_heap<int> mh( 11 );
        mh.insert(3 );
        mh.insert( 2 );
        mh.delete_key( 1 );
        mh.insert(15 );
        mh.insert( 5 );
        mh.insert( 4 );
        mh.insert( 45 );
        std::cout << mh.extract_min() << " ";
        std::cout << mh.get_min() << " ";
        mh.decrease_key( 2, 1 );
        std::cout << mh.get_min() << std::endl;
        return 0;
    }

}
