#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>

//ITMO course, binary search question 3B

//f(x1, x2, ... sizes of segments) = max_{over k segments} sum of elements in a segment
//To minimize this function
//to check if f(x1, x2, .. sizes of segments) <= t? each segement's sum must be <= t
//go from left to right and see if you can make k segments whose sum <= t

int n, k;
std::vector<int> arr;

//First count how many segments are possible whose sums are less than or equal to mid
bool good(long long mid)
{
    int segment_count = 0;
    long long segment_sum = 0;
    int current_index = 0;

    for (int right = 0; right < n; ++right)
    {
        //Important point: If any single value is greater than the mid vlaue no sgements can be formed
        if (arr[right] > mid)
        {
            return false;
        }

        segment_sum += arr[right];
        if (segment_sum > mid)
        {
            segment_sum = arr[right];
            segment_count += 1;
        }
    }
    segment_count++;

    if (segment_count <= k)
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
    std::cin >> n >> k;
    arr.resize(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }

    //left is bad cause there will be no segment division where sum of each segement is less than equal to 0
    long long left = 0;

    long long right = 1e15;

    while (left+1 < right)
    {
        long long mid = left+(right-left)/2;

        if (good(mid))
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    std::cout << right;
}