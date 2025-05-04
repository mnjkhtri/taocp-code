#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits>
#include <cmath>
#include <numeric>

//https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/D
//Binary search, ITMO course, problem 2D

#define int long long

int no_of_balloons, no_of_assistants;
std::vector<std::vector<int>> tzy;
std::vector<int> each_assistant;

bool good(long long mid)
{
    //whether they can inflate no_of_balloons in 'mid' time
    long long total_balloons = 0;
    for (int i = 0; i < no_of_assistants; ++i)
    {
        long long each_balloons = 0;
        each_balloons += tzy[i][1]*(mid/(tzy[i][0]*tzy[i][1]+tzy[i][2]));
        long long remaining_time = mid % (tzy[i][0]*tzy[i][1]+tzy[i][2]);

        each_balloons += std::min(remaining_time/tzy[i][0], tzy[i][1]);
    
        each_assistant[i] = each_balloons;
        total_balloons += each_balloons;
    }
    if (total_balloons >= no_of_balloons) return true; else return false;
}

void solve()
{
    std::cin >> no_of_balloons >> no_of_assistants;
    tzy.resize(no_of_assistants);
    each_assistant.resize(no_of_assistants);

    for (int i = 0; i < no_of_assistants; ++i)
    {
        int tmp;
        std::cin >> tmp; tzy[i].push_back(tmp);
        std::cin >> tmp; tzy[i].push_back(tmp);
        std::cin >> tmp; tzy[i].push_back(tmp);
    }
    //search space is time

    // if(no_of_balloons == 0)
    // {
    //     std::cout << 0 << std::endl;
    //     for(int i=0; i<no_of_assistants; i++) {
    //         std::cout << "0 ";
    //     }
    //     return;
    // }

    long long left = -1; //cant be one because no of balloons could be zero
    long long right = INT_MAX;
    while (left+1 < right)
    {
        long long mid = left+(right-left)/2;
        if (good(mid)) right = mid;
        else left = mid;
    }

    std::cout << right << std::endl;

    good(right);

    for (int i = 0; i < no_of_assistants; ++i)
    {
        //each assistant will either make balloons in his capacity or make required no of balloons
        std::cout << std::min(each_assistant[i], no_of_balloons) << " ";
        no_of_balloons -= std::min(each_assistant[i], no_of_balloons);
    }
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

