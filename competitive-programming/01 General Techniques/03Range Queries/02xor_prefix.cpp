#include <ios>
#include <iostream>
#include <vector>

//Prefix sums for xors
int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    scanf("%d", &n);
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }

    std::vector<unsigned long long> prefixSum(n+1,0);
    for (int i = 0; i < n; ++i)
    {
        prefixSum[i+1] = prefixSum[i]^arr[i];
    }

    // for (int i = 0; i < n+1; ++i)
    // {
    //     std::cout << prefixSum[i] << " ";
    // }
    // std::cout << std::endl << std::endl;

    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; ++i)
    {
        int left, right;
        scanf("%d%d", &left, &right);

        printf("%lld\n", prefixSum[right]^prefixSum[left-1]);
    }
}