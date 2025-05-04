#include <iostream>
#include <vector>
#include <map>
#include <set>

//Codeforces ITMO pilo course:
//Binary search, step1, problem C
int main()
{
    long long n,k;
    std::cin >> n >> k;

    std::vector<long long> arr(n);
    for (long long i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }

    for (int i = 0; i < k; ++i)
    {
        long long find;
        std::cin >> find;

        long long left = -1;
        long long right = n;

        while (left+1 < right)
        {
            long long mid = (left+right)/2;
            if (arr[mid] >= find)
            {
                right = mid;
            }
            else
            {
                left = mid;
            }
        } 
        std::cout << right+1 << std::endl;
    }
   
}