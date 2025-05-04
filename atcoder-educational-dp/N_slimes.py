import sys
sys.setrecursionlimit(10**9)
n = int(input())
sizes = [int(x) for x in input().split()]
INF = sys.maxsize

slimes = [[-1 for i in range(n)] for i in range(n)]

for diff in range(n):
  for left in range(n-diff):
    right = left+diff
    if right == left:
      retval = 0
    else:
      retval = INF
      adds = 0
      for i in range(left,right+1):
        adds += sizes[i]
      for i in range(left,right):
        retval = min(retval, slimes[left][i]+slimes[i+1][right]+adds)
    slimes[left][right] = retval
      
print(slimes[0][n-1])
  