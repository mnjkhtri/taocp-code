#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>

//Given a string, task is to sort the suffix arrays
//One way is to generate all the suffixes and do std::sort (exceeds limits as is O(N^2) in memory and also hard on time)

int main()
{
    std::string s;
    std::cin >> s;
    s.push_back('$');
    std::vector<std::pair<std::string,int>> suffixes(s.size());

    for (int i = 0; i < s.size(); ++i)
    {
        suffixes[i].first = s.substr(i,s.size()-i);
        suffixes[i].second = i;
    }
    std::sort(suffixes.begin(), suffixes.end());

    for (int i = 0; i < s.size(); ++i)
    {
        std::cout << suffixes[i].second << " ";
    }
}