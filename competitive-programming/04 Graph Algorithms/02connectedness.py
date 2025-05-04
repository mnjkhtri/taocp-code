vertices = 7 #goes from 0 to 9
edges = 4
adj = [[] for _ in range(vertices)]
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  adj[temp[0]].append(temp[1])
  adj[temp[1]].append(temp[0])

visited = [False for _ in range(vertices)]
dfslist = []
def dfs(current):
    dfslist.append(current)
    visited[current] = True
    for adjacents in adj[current]:
        if not visited[adjacents]:
            dfs(adjacents)

count = 0
for node in range(vertices):
  if not visited[node]:
    count += 1 
    dfs(node)
    dfslist.append("-")
print(dfslist)

#test input
""""
0 1
1 2
2 3
4 5

0 1       4 5       6
2 3
"""