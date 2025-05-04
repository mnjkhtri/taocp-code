import sys
sys.setrecursionlimit(10**9)

n,m = [int(x) for x in input().split()]
vert = [[] for i in range(n)] 
for i in range(m):
  first,second = [int(x) for x in input().split()]
  vert[first-1].append(second-1)

memo = [-1 for i in range(n)]
def DFS(i):
  if memo[i]!=-1:
    return memo[i]
  count = 0
  for nv in vert[i]:
    count = max(count, DFS(nv)+1)
  memo[i] = count
  return count

res = 0
for i in range(n):
  res = max(res,DFS(i))
print(res)