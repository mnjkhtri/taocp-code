vertices = 10 #goes from 0 to 9
edges = 11
adj = [[] for _ in range(vertices)]
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  adj[temp[0]].append(temp[1])
  adj[temp[1]].append(temp[0])

visited = [False for _ in range(vertices)]
dfslist = []
def dfs(current):
    #do something to the nodes before visiitng its adjacents nodes
    dfslist.append(current)
    visited[current] = True
    for adjacents in adj[current]:
        if not visited[adjacents]:
            #do something to the unvisited adjacents
            dfs(adjacents)
        #else:
            #can also do something to already visited children
    #do something to the nodes after visiting its adjacents (the nodes here go from bottom to top)


dfs(0)
print(dfslist)

#test input
""""
7 4
9 7
5 4
0 4
3 7
1 9
2 5
8 1
0 6
4 3
6 5
this graph looks something like the following tree but with 4-3 connected and 5-6 connected

            0
        4       6
    7       5 
  9   3     2
  1
  8
"""