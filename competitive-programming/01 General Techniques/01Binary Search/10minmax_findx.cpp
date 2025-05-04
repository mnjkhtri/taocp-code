#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits>

//https://codeforces.com/contest/1730/problem/B

int n;
std::vector<int> dresstime;
std::vector<int> coor;

bool good (double mid)
{
    //know whether f(x) <= for any values of x
    //ti + |xi-x0| <= mid 
    //|x0-xi| <= mid-ti
    //x0 lies on xi-(mid-ti), xi+(mid-ti)
    double left_boundary = coor[0]-(mid-dresstime[0]);
    double right_boundary = coor[0]+(mid-dresstime[0]);

    for (int i = 1; i < n; ++i)
    {
        left_boundary = std::max(left_boundary, coor[i]-(mid-dresstime[i]));
        right_boundary = std::min(right_boundary, coor[i]+(mid-dresstime[i]));
    }
    return (right_boundary > left_boundary);
}

void solve()
{
    std::cin >> n;
    coor.resize(n);
    dresstime.resize(n);
    for (int i = 0; i < n; ++i) std::cin >> coor[i];
    for (int i = 0; i < n; ++i) std::cin >> dresstime[i];

    //f(x) = maximum time required to meet at position x = max_{over i}(something)
    //Goal = to minimize this function

    double left = -1; //nobody meets at -1 second
    double right = 1e30; //max possible idk
    
    for (int t = 0; t < 400; ++t)
    {
        double mid = (right+left)/2;
        if (good(mid)) right = mid;
        else left = mid;
    }
    //the minimum time required is on right variable;
    //extract location from it
    
    double left_boundary = coor[0]-(right-dresstime[0]);
    double right_boundary = coor[0]+(right-dresstime[0]);

    for (int i = 1; i < n; ++i)
    {
        left_boundary = std::max(left_boundary, coor[i]-(right-dresstime[i]));
        right_boundary = std::min(right_boundary, coor[i]+(right-dresstime[i]));
    }    //from 0th person:
    std::cout << std::setprecision(20) << left_boundary << std::endl;
}

int main()
{
    int t;
    std::cin >> t;
    // t = 1;
    while (t--)
    {
        solve();
    }
}

