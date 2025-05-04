/*
Given an array find its (i,j) segment sum
For k queries takes O(Nk)
But make a prefix array in O(N) then do it on O(1) for each query so O(N+k)
Works for static arrays only that would not change in future
*/
#include <ios>
#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    scanf("%d",&n);
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d",&arr[i]);
    }

    //Two ways of doing prefix sums:
    //prefixSum[i] = sum of elements from 0th to ith element
        //-size N, bad queries
    //prefixSum[i] = sum of elements from 0th to i-1th element
        //-size N+1 (extra 0), good intuitive queries, prefix sums stay on the boundary of the original array and is the sum of all the elements on the left of it

    std::vector<long long> prefixSum(n+1,0);

    for (int i = 0; i < n; ++i)
    {
        prefixSum[i+1] += prefixSum[i]+arr[i];
    }

    // //Prints the prefix sums
    // for (int i = 0; i < n+1; ++i)
    // {
    //     std::cout << prefixSum[i] << " ";
    // }
    // std::cout << std::endl;

    int left, right;
    int k;
    scanf("%d",&k); 
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%d", &left, &right);
        printf("%lld\n", prefixSum[right] - prefixSum[left-1]);
    }
    //The sum of elements on the half interval [left,right) is given by: prefixSum[right]-prefixSum[left]
}

//The prefix cannot be applied to mininum or maximum property as they are not reversible
//The addition operation can be generalized to associative operators, and prefix array is initialized with indentiy value
//One such operation is XOR