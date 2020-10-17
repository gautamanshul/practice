#include <iostream>
#include <vector>
#include <algorithm>

namespace priority_queue
{
    template <class  T, class cmp = std::less<T>>
    class priority_queue
    {
    public:
        priority_queue();

        void insert(const T & elem);
        void swim(int index);
        void print();
        void pop();
        void decrease_key(int index, int val);
        const T & top() const;
        T extract_min();
    private:
        void heapify(int i);
        std::vector<T>  elements;

    protected:
        cmp compare;
    };

    template <class T, class cmp>
    priority_queue<T,cmp>::priority_queue()
    {}

    template <class T, class cmp>
    void priority_queue<T,cmp>::swim(int index)
    {
        for( int i = (index - 1)/2; i >= 0 && compare(elements[index], elements[i]); index = i, i = (i-1)/2 )
        {
            std::swap(elements[index], elements[i]);
        }
    }

    template <class T, class cmp>
    void priority_queue<T,cmp>::decrease_key(int index, int val)
    {
        elements[index] = val;
        swim(index);
    }

    template <class T, class cmp>
    const T & priority_queue<T,cmp>::top() const {
        if (!elements.empty()) {
            return elements[0];
        }
    }

    template <class T, class cmp>
    void priority_queue<T,cmp>::heapify(int index)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < elements.size() && compare(elements[left], elements[smallest]))
        {
            smallest = left;
        }

        if (right < elements.size() && compare(elements[right], elements[smallest]))
        {
            smallest = right;
        }

        if ( smallest != index)
        {
            std::swap(elements[smallest], elements[index]);
            heapify(smallest);
        }
    }

    template <class T, class cmp>
    T priority_queue<T,cmp>::extract_min()
    {
        T tmp;
        if (!elements.empty()) {

            tmp = elements[0];

            if ( elements.size() > 1) {
                elements[0] = elements[elements.size() - 1];
                elements[elements.size() - 1] = tmp;
                elements.pop_back();
                heapify(0);
            }
        }
        return tmp;
    }

    template <class T, class cmp>
    void priority_queue<T,cmp>::insert(const T & elem)
    {
        elements.push_back(elem);
        swim(elements.size() - 1);
    }

    template <class T, class cmp>
    void priority_queue<T,cmp>::print()
    {
        std::cout << "Heap is: " << std::endl;
        std::for_each(elements.begin(),elements.end(), [] (const T & val) { std::cout << val << " "; });
        std::cout << std::endl;
    }
}

int main()
{
    priority_queue::priority_queue<int> pq;

    pq.insert(2);
    pq.insert(3);
    pq.insert(5);
    pq.insert(1);
    pq.insert(7);
    pq.insert(10);

    pq.print();

    int tmp = pq.extract_min();
    pq.print();

    std::cout << "Extracted min: " << tmp << std::endl;
}