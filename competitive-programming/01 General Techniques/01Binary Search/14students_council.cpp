#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <limits>

//https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/G
//ITMO course codefroces, binary search problem 2G

#define int long long

int council_size;
int no_of_groups;
std::vector<int> students_in_group_i;

bool good(int mid)
{
    //To know whether we can make 'mid' number of councils (think in terms of passive voice)
    //If we make mid number of councils then there are 'mid'*size slots where each students from each group go uniquely
    //Frome one group either all students leave or some leave to fill one slot in the 'mid' councils
    //We place them optimally
    //count the number of students that can go which if greater than the number we hold, true, else false

    int slots = council_size*mid;
    for (int i = 0; i < no_of_groups; ++i)
    {
        slots -= std::min(mid, students_in_group_i[i]);
    }    
    return (slots <= 0);
}

void solve()
{
    std::cin >> council_size;
    std::cin >> no_of_groups;
    students_in_group_i.resize(no_of_groups);

    for (int i = 0; i < no_of_groups; ++i) std::cin >> students_in_group_i[i];
    //To make councils of size k where each students are from different groups
    //Max number of councils that could be made??
    //You can definitely make 0 councils, if you can make k councils then you can make k-1 councils
    //If you cannot make k councils, then you cannot make k+1 councils, also you cannot make say 1e10 councils

    int left = 0;
    int right = 1e16; //number of councils that are impossible to make??

    while (left+1 < right)
    {
        int mid = (left+right)/2;
        if (good(mid)) left = mid;
        else right = mid;
    }
    std::cout << left;
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

