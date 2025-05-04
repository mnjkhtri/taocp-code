#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <limits>

#define int long long

//1700 ratings
//https://codeforces.com/contest/779/problem/D

//OR

//Itmo course binary search problem 2F

std::string t, p;
std::vector<int> removals;

bool good(int mid)
{
    std::string tnew = t;
    for (int i = 0; i < mid; ++i)
        tnew[removals[i]-1] = '*';

    //need to check whether string p can be made from new string tnew
    int ppntr = 0;
    for (int i = 0; i < tnew.size(); ++i)
    {
        if (tnew[i] == p[ppntr]) ppntr++;
        if (ppntr == p.size()) return true;
    }
    return false;
}

void solve()
{
    std::cin >> t;
    std::cin >> p;

    removals.resize(t.size());
    for (int i = 0; i < t.size(); ++i) std::cin >> removals[i];

    //With maximum possible removals need p as substring in t;
    //0 removals - yes possible to go; 1, 2, 3, ... (possible)
    //n removals - not possitlbe to do; n-1, n-2, ... (not possibles)
    //0(yes) 1(yes) ... ?(no) ?(no) ?(no) ... no(n);

    int left = 0; //trues
    int right = t.size()+1; //falses (to be on the safe side)

    while (left+1 < right)  //Until left points to last yes and right points to first no
    {
        int mid = left+(right-left)/2;  //mid = (l+r)/2
        if (good(mid)) left = mid;
        else right = mid;
    }

    std::cout << left;
}

signed main()
{
    int t;
    // std::cin >> t;
    t = 1;
    while (t--)
    {
        solve();
    }
}

