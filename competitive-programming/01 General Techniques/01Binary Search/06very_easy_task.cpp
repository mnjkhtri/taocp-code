#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>

//Code forces ITMO course:
//Binary search, step 2, problem D solution:

int n, x, y;

bool good(long long mid)
{
    long long total = 0;
    //Meaning that if time is less than both of those then no paper can be made
    if (mid < std::min(x,y))
    {
        total = 0;
    }
    else
    {
        long long remaining_time = mid-std::min(x,y);
        total += 1;
        total += std::floor(remaining_time/x)+std::floor(remaining_time/y);
    }
    if (total >= n) return true; else return false;
}

int main()
{
     std::cin >> n >> x >> y;

    //To search in the space of seconds going from 0 1 2 3 4 5 ... 
    //Where each corresponds as bad bad bad bad .. bad good good good ...
    //Need to find the first good here
    //The (x) second is bad if x < std::min(x,y)*n

    //can make no shit in 0th second;
    long long left = 0;

    //this should be long long else goes out
    long long right = 1e10;

    while (left+1 < right)
    {
        long long mid = (left+right)/2;

        if (!good(mid))
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    std::cout << right << std::endl;
}