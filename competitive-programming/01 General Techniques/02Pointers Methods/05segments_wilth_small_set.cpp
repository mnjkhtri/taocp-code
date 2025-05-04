#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

//Codeforecs ITMO university course:
//Two pointers, step 2, E 
void solve()
{
    int n, k;
    std::cin >> n;
    std::cin >> k;

    if (k == 0)
    {
        std::cout << 0 << std::endl;
        return;
    }

    std::vector<int> arr(n);
    for (int i = 0; i < arr.size(); ++i)
    {
        std::cin >> arr[i];
    }
    std::map<int,int> uniques;
    long long count = 0;
    int left = 0;
    for (int right = 0; right < n; ++right)
    {
        //update the goodness paramter
        uniques[arr[right]]++;
        //While badness is there
        while(uniques.size() > k)
        {
            uniques[arr[left]]--;
            if (uniques[arr[left]] == 0)
            {
                uniques.erase(arr[left]);
            }
            left++;
        }
        count += (right-left+1);
    }
    std::cout << count;
}

int main()
{
    int t;
    // std::cin >> t;
    t = 1;

    for (int i = 0; i < t; ++i)
    {
        solve();
    }
}