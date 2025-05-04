#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>

//Codeforecs ITMO university course:
//Two pointers, step 2, F 
void solve()
{
    int n;
    unsigned long long k;
    std::cin >> n;
    std::cin >> k;

    std::vector<unsigned long long> arr(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }

    int left = 0;
    unsigned long long count = 0;

    std::multiset<unsigned long long> muls;

    for (int right = 0; right < n; ++right)
    {
        //update the parameter
        muls.insert(arr[right]);

        //if in bad zone then increase the left to relief
        while (*muls.rbegin()-*muls.begin() > k)
        {
            //need to use find here mustly
            muls.erase(muls.find(arr[left]));
            left++;
        }

        count += right-left+1;
    }
    std::cout << count << std::endl;
}

int main()
{
    int t;
    // std::cin >> t;
    t = 1;

    for (int i = 0; i < t; ++i)
    {
        solve();
    }
}