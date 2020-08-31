// Solution for https://www.hackerrank.com/challenges/2d-array/problem
//There are  hourglasses in , and an hourglass sum is the sum of an hourglass' values.
// Calculate the hourglass sum for every hourglass in , then print the maximum hourglass sum.

#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <vector>
#include <limits>
    #include <queue>

int hour_glass( std::vector<std::shared_ptr<std::vector<int>>> arr )
{
    auto cmp = [] (int left, int right) {return left < right;};
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp); // push O(log(n)), pop O(1)
    for ( int i = 0; i < 4 ; ++i) {
        for(int j = 0; j < 4; ++j ) {
            int sum = arr[i]->at(j) + arr[i]->at(j + 1) + arr[i]->at(j + 2) + arr[i + 1]->at(j + 1) +
                  arr[i + 2]->at(j) + arr[i + 2]->at(j + 1) + arr[i + 2]->at(j + 2);
            pq.push(sum);
        }
    }
    return pq.top();
}

std::vector<std::string>  split_string(std::string  in)
{
    // Remove consecutive spaces from the string
    std::string::iterator new_end = std::unique(in.begin(), in.end(),
                                        [](const char &x, const char &y) { return x == y && x == ' ';});

    in.erase(new_end, in.end());
    size_t j = 0;
    while(in[j] == ' ')
    {
        in.erase(j);
        ++j;
    }
    while(in[in.length()-1] == ' ')
    {
        in.pop_back();
    }

    std::vector<std::string>  splits;
    char delimiter = ' ';
    size_t i = 0;
    size_t pos = in.find(delimiter);

    while( pos != std::string::npos )
    {
        splits.push_back(in.substr(i, pos-i));
        i = pos + 1;
        pos = in.find(delimiter,i);
    }
    splits.push_back(in.substr(i, std::min(pos, in.length()) - i + 1));
    return splits;
}

int main()
{
    std::ofstream fout("c:/Users/anshu/CLionProjects/practice/hour_glass.txt");
    std::vector<std::shared_ptr<std::vector<int>>> arr(6);
    for( int i = 0; i < 6; ++i )
    {
        arr[i] = std::make_shared<std::vector<int>>( 6);
        std::string  arr_tmp;
        std::getline( std::cin, arr_tmp );
        std::vector<std::string>  split_s = split_string(arr_tmp);

        for(int j = 0; j < arr[i]->size(); ++j )
        {
            int arr_item = std::stoi(split_s[j]);
            arr[i]->at(j) = arr_item;
        }
    }

    int result = hour_glass(arr);
    fout << result << "\n";
    fout.close();
    return 0;
}