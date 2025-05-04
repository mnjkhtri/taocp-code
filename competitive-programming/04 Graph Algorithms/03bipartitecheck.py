from sniffio import current_async_library_cvar


vertices = 10 #goes from 0 to 9
edges = 11
adj = [[] for _ in range(vertices)]
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  adj[temp[0]].append(temp[1])
  adj[temp[1]].append(temp[0])

visited = [False for _ in range(vertices)]
color = [-1 for _ in range(vertices)]

#we go on coloring the unvisited children opposite color to its parent so we do it inside the for loop
#we check the visited node if they are of same color that of their parent
def dfs(current):
    visited[adjacents] = True
    for adjacents in adj[current]:
        if not visited[adjacents]:
          color[adjacents] = 1-color[current]
          if not dfs(adjacents):
            return False
        else:
          if color[current] == color[adjacents]:
            return False


color[0] = 0
print(dfs(0))

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