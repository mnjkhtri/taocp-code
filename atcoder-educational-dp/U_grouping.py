import sys
sys.setrecursionlimit(10**9)

n = int(input())
costs = [[int(x) for x in input().split()] for i in range(n)]

#cost of putting the rabbits in one group where mask can go from 0 to 2**n-1 representing the subsets of rabbits
#O(2^N*N*N)
cost = [0 for i in range(1<<n)]
for mask in range(1<<n):
  for one_rabbit in range(n):
    for another_rabbit in range(one_rabbit+1,n):
      if mask & (1<<one_rabbit) and mask & (1<<another_rabbit):
        cost[mask] += costs[one_rabbit][another_rabbit]
  
#for eg if mask=110 then submask are: 000, 100, 010, 110
INF = sys.maxsize
memo = [-1 for i in range(1<<n)]
memo[0] = 0
def total_costs(mask):
  if memo[mask] != -1:
    return memo[mask]
  sub = mask
  total = -INF
  while sub > 0:
    total = max(total, cost[sub]+total_costs(mask^sub))
    sub = (sub-1)&mask
  memo[mask] = total
  return total

print(total_costs((1<<n)-1))