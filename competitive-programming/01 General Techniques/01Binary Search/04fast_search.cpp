#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>


//Codeforces ITMO course:
//Binary search, step 1, problem D
int main()
{
    long long n,k;
    std::cin >> n;

    std::vector<long long> arr(n);
    for (long long i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }

    std::cin >> k;
    std::sort(arr.begin(), arr.end());

    for (int i = 0; i < k; ++i)
    {
        long long l;
        long long r;
        std::cin >> l >> r;

        long long left = -1;
        long long right = n;

        while (left+1 < right)
        {
            long long mid = (left+right)/2;
            if (arr[mid] < l)
            {
                left = mid; 
            }
            else
            {
                right = mid;
            }
        } 
        long long strictly_less_than_l = left;

        //Another search
        left = -1;
        right = n;

        while (left+1 < right)
        {
            long long mid = (left+right)/2;
            if (arr[mid] <= r)
            {
                left = mid; 
            }
            else
            {
                right = mid;
            }
        } 
        long long less_than_equal_r = left;

        std::cout << less_than_equal_r-strictly_less_than_l << std::endl;
    }
   
}