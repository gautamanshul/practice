#ifndef PRACTICE_PRIORITY_QUEUE_V1_HPP
#define PRACTICE_PRIORITY_QUEUE_V1_HPP
namespace priority_queue {
    template<class T, class cmp = std::less <T>>
    class priority_queue {
    public:
        priority_queue();

        void insert(const T &elem);

        void swim(int index);

        void print();

        void pop();

        void decrease_key(int index, int val);

        const T &top() const;

        T extract_min();

    private:
        void heapify(int i);

        std::vector <T> elements;

    protected:
        cmp compare;
    };
}

#endif //PRACTICE_PRIORITY_QUEUE_V1_HPP
