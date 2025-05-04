#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>

//A good question on binary search and prefix sum together
//https://codeforces.com/problemset/problem/474/B

int n;
std::vector <int> worms;
std::vector <int> prefixSums;
int wormNo;

bool good(long long mid)
{
    if (prefixSums[mid] >= wormNo) return true; else return false;
}

void solve()
{
    std::cin >> n;
    worms.resize(n);
    prefixSums.resize(n+1);
    prefixSums[0] = 0;

    for (int i = 0; i < n; ++i) std::cin >> worms[i];

    for (int i = 0; i < n; ++i) 
        prefixSums[i+1] = prefixSums[i] + worms[i];

    // for (int i = 0; i < n; ++i) 
    //     std::cout << prefixSums[i] << " ";
    // std::cout << std::endl;

    int m;
    std::cin >> m;
    //to know which pile nth worm is? last prefixsum for which worm no <= prefix sum then index is the pile number

    while (m--)
    {
        std::cin >> wormNo;
        long long left = 0; //bad
        long long right = n+1; //good

        while (left+1 < right)
        {
            long long mid = (left+right)/2;
            if (good(mid)) right = mid; else left = mid;
        }
        std::cout << right << std::endl;
    }
}

int main()
{
    int t;
    // std::cin >> t;
    t = 1;
    while (t--)
    {
        solve();
    }
}

