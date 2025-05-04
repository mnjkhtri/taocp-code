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

int unit_breads, unit_saugsages, unit_cheese;
int breads, sausages, cheese;
int cost_b, cost_s, cost_c;

bool good(int mid)
{
    //whether we can make 'mid' number of burgers
    //assume we can make them then what should follow?
}

void solve()
{
    std::string burger;
    std::cin >> burger;

    unit_breads = std::count(burger.begin(), burger.end(), 'B');
    unit_saugsages = std::count(burger.begin(), burger.end(), 'S');
    unit_cheese = std::count(burger.begin(), burger.end(), 'C');

    std::cin >> breads >> sausages >> cheese;

    std::cin >> cost_b >> cost_s >> cost_c;

    int total_cost; std::cin >> total_cost;

    int left = 0; // can definitely make 0 burgers
    int right = std::max(breads+total_cost/cost_b, sausages+total_cost/cost_s);
    right = std::max(right, cheese+total_cost/cost_c);

    while (left+1 < right)
    {
        int mid = (left+right)/2;
        if (good(mid)) left = mid; else right = mid;
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

