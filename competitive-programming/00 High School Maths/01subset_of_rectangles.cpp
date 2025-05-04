#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>

//https://codeforces.com/gym/306143/problem/A

//From each row and each column find the number of elements with same color that would make a set
//Then add the number of subsets possible from them

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> ele(n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            int check;
            std::cin >> check;
            ele[i].push_back(check);
        }

    unsigned long long count = 0;
    for (int row = 0; row < n; ++row)
    {
        long long black = 0;
        long long white = 0;
        //fow rowth row:
        for (int col = 0; col < m; ++col)
        {
            if (ele[row][col] == 1)
            {
                black++;
            }
            else
            {
                white++;
            }
        }
        count += (1LL<<white) -1;
        count += (1LL<<black) -1;
    }

    for (int col = 0; col < m; ++col)
    {
        unsigned long long black = 0;
        unsigned long long white = 0;
        //fow rowth row:
        for (int row = 0; row < n; ++row)
        {
            if (ele[row][col] == 1)
            {
                black++;
            }
            else
            {
                white++;
            }
        }

        count += (1LL<<black) -1;
        count += (1LL<<white) -1;
    }

    std::cout << count-m*n;
}

