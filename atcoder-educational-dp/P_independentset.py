import sys
sys.setrecursionlimit(10**9)
n = int(input())
adj = [[] for i in range(n)]
for _ in range(n-1):
  temp = [int(x) for x in input().split()]
  adj[temp[0]-1].append(temp[1]-1)
  adj[temp[1]-1].append(temp[0]-1)

white = 0
black = 1
modder = 10**9+7

parents = [-1]*n
parents[0] = -1

def find_parents(node):
  for adjacents in adj[node]:
    if adjacents != parents[node]:
      parents[adjacents] = node
      find_parents(adjacents)

find_parents(0)

memo = [[-1 for i in range(12)] for j in range(n)]

def ways(node, color):
  if memo[node][color] != -1:
    return memo[node][color]
  parent = parents[node]
  if color == white:
    product = 1
    for vertices in adj[node]:
      if vertices != parent:
        product *= ways(vertices,white)+ways(vertices,black)
  else:
    product = 1
    for vertices in adj[node]:
      if vertices != parent:
        product *= ways(vertices,white)
  memo[node][color] = product
  return product

print((ways(0,white)+ways(0,black))%modder)