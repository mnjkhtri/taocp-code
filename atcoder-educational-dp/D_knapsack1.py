import sys
sys.setrecursionlimit(1000000)
n = int(input())
h = [[int(x) for x in input().split()] for i in range(n)]
whichone = [-1]*n
memo = {}
def maxhappiness_doing_i(n,i):
    if (n,i) in memo:
        return memo[(n,i)]
    if n == -1:
        m = 0
    else:
        if i == 0:
            m = max(maxhappiness_doing_i(n-1,1), maxhappiness_doing_i(n-1,2))
        elif i == 1:
            m = max(maxhappiness_doing_i(n-1,0), maxhappiness_doing_i(n-1,2))
        else:
            m = max(maxhappiness_doing_i(n-1,0), maxhappiness_doing_i(n-1,1))
        m += h[n][i]
    memo[(n,i)] = m
    return m
print(max(maxhappiness_doing_i(n-1,0),maxhappiness_doing_i(n-1,1),maxhappiness_doing_i(n-1,2)))