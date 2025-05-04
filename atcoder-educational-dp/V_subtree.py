#This is not the solution rather the DFS variations
import sys
sys.setrecursionlimit(10**9)

n,md = [int(x) for x in input().split()]
adj = [[] for i in range(n)]
for _ in range(n-1):
  temp = [int(x) for x in input().split()]
  adj[temp[0]-1].append(temp[1]-1)
  adj[temp[1]-1].append(temp[0]-1)

#number of ways to paint the subtrees when root is fixed
dp = [1]*n

def dfs(start_node,parent=0):
  #action on start_node after entering it
  initialize = 1
  for adjacents in adj[start_node]:
    if adjacents == parent:
      continue
    #action on child before entering it
    dfs(adjacents,start_node)
    #action on child after exiting it
    initialize *= dp[adjacents]%md
  #action on start_node before exiting it
  dp[start_node] = (initialize+1)%md
dfs(0)

dpa = [1]*n
def dfs_again(start_node, parent=0):
  
  pre = dpa[start_node]
  for adjacents in adj[start_node]:
    if adjacents == parent:
      continue
    dpa[adjacents] = (dpa[adjacents]*pre)%md
    pre = (pre*dp[adjacents])%md
    
  pre = 1
  for adjacents in reversed(adj[start_node]):
    if adjacents == parent:
      continue
    dpa[adjacents] = (dpa[adjacents]*pre)%md
    pre = (pre*dp[adjacents])%md
    
  for adjacents in adj[start_node]:
    if adjacents == parent:
      continue
    dpa[adjacents] = (dpa[adjacents]+1)%md
    dfs_again(adjacents,start_node)
    
dfs_again(0)
#print(dp)
#print(dpa)
for i in range(n):
  print(((dp[i]-1)*dpa[i]+md)%md)