#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>

//Codeforces ITMO pilot course
//Binary search step 2, question A

std::vector<std::pair<int,int>> position_speed;
int n;

//Check if in mid time, everybody can reach there or not
bool good(double mid)
{
    double left_boundary = position_speed[0].first-position_speed[0].second*mid;
    double right_boundary = position_speed[0].first+position_speed[0].second*mid;

    for (int i = 1; i < n; ++i)
    {
        left_boundary = std::max(left_boundary, position_speed[i].first-position_speed[i].second*mid);
        right_boundary = std::min(right_boundary, position_speed[i].first+position_speed[i].second*mid);
    }

    if (right_boundary >= left_boundary)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    std::cin >> n;

    position_speed.resize(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> position_speed[i].first >> position_speed[i].second; 
    }
    //For 0 time its false that they cannot reach anywhere
    double left = 0;
    //farthest distance is 10^18 and slowest speed is 1 so all the time in the world is
    double right = 1e19;

    for (int t = 0; t < 100; ++t)
    {
        double mid = (left+right)/2;
        if (good(mid))
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    std::cout << std::setprecision(20) << right;
}