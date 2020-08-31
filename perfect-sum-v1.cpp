
/// https://www.geeksforgeeks.org/perfect-sum-problem/?ref=leftbar-rightbar
/// Input: arr[] = {5, 10, 12, 13, 15, 18}, K = 30
/// Output: {12, 18}, {5, 12, 13}, {5, 10, 15}
/// Explanation:
/// Subsets with sum 30 are:
/// 12 + 18 = 30
/// 5 + 12 + 13 = 30
/// 5 + 10 + 15 = 30
#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <set>

namespace perfect_sum_v1 {
    template <typename T>
    std::shared_ptr<std::vector<T>> perfect_sum(std::vector<T>  arr, int  k)
    {
        std::shared_ptr<std::vector<T>>  targets;
        std::set<int> sum;
        int current_sum = 0;
        for( int i = 0; i < arr.size(); ++i )
        {
            int current_sum = current_sum + arr[i];
            if ( current_sum > k ) // drop arr[i] move to the next item
            if ( sum.find(arr(i)) == sum.end() )
            {

            }
        }
    }
    int main() {
        std::vector<int> arr{5, 10, 12, 13, 15, 18};

    }

}

