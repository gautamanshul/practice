// Consider an algorithm that takes as input a positive integer n. If n is even, the algorithm divides it by two, and if n is odd, the algorithm multiplies
// it by three and adds one.The algorithm repeats this, until n is one. For example, the sequence for n=3 is as follows:
//3→10→5→16→8→4→2→1
//Your task is to simulate the execution of the algorithm for a given value of n.
//Input
//        The only input line contains an integer n.
// Output
//        Print a line that contains all values of n during the algorithm.
// Constraints
// 1≤n≤106
// Example
//        Input:
// 3
// Output:
// 3 10 5 16 8 4 2 1
#include <iostream>
#define ll long long

namespace weird {

    class weird_algo {
    public:
        weird_algo(size_t in) : in(in) {}

        void run();

    private:
        size_t in;
    };

    void weird_algo::run() {

        size_t n = in;
        while (n != 1) {
            if (n % 2 == 0) {
                std::cout << n << " ";
                n = n / 2;
            } else {
                std::cout << n << " ";
                n = n * 3 + 1;
            }
        }
        std::cout << n;
    }

    int main() {
        size_t n;
        std::cin >> n;
        weird_algo wa(n);
        wa.run();
        return 0;
    }

}