#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits>
#include <cmath>
#include <numeric>

#define int long long

void solve()
{
    double c;
    std::cin >> c;
    //the equation is x^2+sqrt(x)-c = 0; 
    //is a monotonic function at its best

    double left = 0; //gives negative value for this
    double right = c; //definitely gives the positive value

    for (int t = 0; t < 100; ++t)
    {
        double mid = (left+right)/2;
        if ((std::sqrt(mid)+mid*mid-c)<0) left = mid; else right = mid;
    }
    std::cout << std::setprecision(20) << left;
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

