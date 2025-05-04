#include <ios>
#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::vector<int>> arr(n, std::vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            scanf("%d", &arr[i][j]);
        }


    //Now make prefix 2D array:

    std::vector<std::vector<long long>> prefixSum(n+1, std::vector<long long>(m+1,0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            prefixSum[i+1][j+1] = prefixSum[i+1][j] + prefixSum[i][j+1] + arr[i][j] - prefixSum[i][j];

    int k;
    scanf("%d", &k);

    while(k--)
    {
        int i,j,ii,jj;
        scanf("%d%d%d%d", &i, &j, &ii, &jj);

        //Just like in two dimension, left ones were one subtracted here also i's and j's will be
        printf("%lld\n", prefixSum[ii][jj] - prefixSum[i-1][jj] - prefixSum[ii][j-1] + prefixSum[i-1][j-1]);

    }
}