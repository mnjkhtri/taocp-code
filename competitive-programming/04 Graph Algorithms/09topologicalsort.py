from concurrent.futures import process


vertices = 6
edges = 7
adj = [[] for _ in range(vertices)]
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  adj[temp[0]].append(temp[1])

visited = [False for _ in range(vertices)]

#in topological sorting we maintain the status of each node in three cases:
#1) unprocesed 2) uprocessing 3) processed

topoorder = []
def dfs(current):
    visited[current] = True
    for adjacents in adj[current]:
        if not visited[adjacents]:
            dfs(adjacents)
    topoorder.append(current)

for each_vertex in range(vertices):
    if not visited[each_vertex]:
        dfs(each_vertex)

print(topoorder)
"""
0 1 2
3 4 5 

->
0 1
1 2
3 0
4 1
3 4
4 2
2 5


->
0 1
1 2
3 0
4 1
3 4
2 4
2 5
"""