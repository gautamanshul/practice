#include <bits/stdc++.h>
#include <iostream>
#include <string>

namespace reverse_pint {
    std::vector<std::string> split_string(std::string);

// Reverse array function

    template<typename T>
    std::vector<T> reverse_array(const std::vector<T> &a) {
        std::vector<T> rev;
        T tmp;
        rev.resize(a.size());
        for (int i = a.size() - 1, j = 0; i != 0; --i, j++) {
            tmp = a[i];
            rev[i] = a[j];
            rev[j] = tmp;
        }

        return rev;
    }

    std::vector<std::string> split_string(std::string in) {
        std::string::iterator new_end = std::unique(in.begin(), in.end(),
                                                    [](const char &x, const char &y) { return x == y && x == ' '; });

        in.erase(new_end, in.end());
        while (in[in.length() - 1] == ' ') {
            in.pop_back();
        }

        std::vector<std::string> splits;
        char delimiter = ' ';
        size_t i = 0;
        size_t pos = in.find(delimiter);

        while (pos != std::string::npos) {
            splits.push_back(in.substr(i, pos - i));
            i = pos + 1;
            pos = in.find(delimiter, i);
        }
        splits.push_back(in.substr(i, std::min(pos, in.length()) - i + 1));
        return splits;
    }

    int main() {
        std::ofstream fout("c:/Users/anshu/CLionProjects/practice/rev.txt");
        int arr_count;
        std::cin >> arr_count;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string arr_tmp;
        std::getline(std::cin, arr_tmp);

        std::vector<std::string> split_s = split_string(arr_tmp);
        std::vector<int> arr(arr_count);

        for (int i = 0; i < arr_count; ++i) {
            int arr_item = std::stoi(split_s[i]);
            arr[i] = arr_item;
        }

        std::vector<int> res = reverse_array(arr);

        for (int i = 0; i < res.size(); ++i) {
            fout << res[i];
            if (i != res.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
        fout.close();
        return 0;
    }

}