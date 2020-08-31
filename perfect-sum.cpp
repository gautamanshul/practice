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
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

namespace perfect {
    class perfect_sum;

    typedef boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int>>>> tuple_t;

    class perfect_sum {
    public:
        perfect_sum(const std::vector<int> &arr, const int target);

        find_tuples();

        typedef boost::shared_ptr<perfect_sum> perfect_sum_ptr;

    private:
        int target_;
        std::vector<int> arr_;
        tuple_t tuple_;
    };

    perfect_sum::find_tuples() {
        int sum = 0;
        for (int i = 0; i < arr_.size(); ++i) {

            if (sum == target_) {
                sum = 0;
                if (!tuple_) {
                    //tuple_ = boost::make_shared<std::vector<boost::shared_ptr<int>>>();
                    tuple_ = tuple_t();
                    tuple_->push_back(boost::make_shared<std::vector<int>>());
                }
            }
        }
        return sum;
    }

    perfect_sum::perfect_sum(const std::vector<int> &arr, const int target) {
        target_ = target;
        arr_ = arr;
    }

    int main() {
        int arr[]{5, 10, 12, 13, 15, 18};
        std::vector<int> arr1(arr, arr + sizeof(arr) / sizeof(arr[0]));
        int sum = 30;
        perfect_sum::perfect_sum_ptr ps = boost::make_shared<perfect_sum>(arr1, sum);
        return 0;
    }

}