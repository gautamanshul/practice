#include <queue>
#include <iostream>

namespace max_profit {

    int max_profit(int seats[], int size, int people) {
        std::priority_queue<int> pq;
        for (int i = 0; i < size; ++i) {
            pq.push(seats[i]);
        }
        int profit = 0;
        int person = 0;

        while (person < people) {
            int top = pq.top();
            pq.pop();
            if (top == 0) {
                break;
            }
            profit = profit + top;
            pq.push(top - 1);
            person++;
        }
        return profit;
    }

    int main() {
        int seats[] = {2, 3, 4, 5, 1};
        int size = sizeof(seats) / sizeof(int);
        int people = 6;
        std::cout << max_profit(seats, size, people);
        return 0;
    }

}