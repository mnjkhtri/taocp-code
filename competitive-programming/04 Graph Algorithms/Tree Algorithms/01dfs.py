vertices = 10 #goes from 0 to 9
edges = 9
adj = [[] for _ in range(vertices)]
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  adj[temp[0]].append(temp[1])
  adj[temp[1]].append(temp[0])

#O(vertices+edges)
#the visited stack is itself involved in 
dfslist = []
def dfs(current, parent=-1):
    dfslist.append(current)
    #do something to the node before visiting its subtrees (the nodes here go from top to bottom)
    for adjacents in adj[current]:
        if adjacents != parent:
            #do something to its children
            dfs(adjacents, current)
    #do something to the nodes after visiting its subtrees (the nodes here go from bottom to top)
    print(current)

dfs(0)
print(dfslist)

#bfs is quite difficult to implement and there is a queue involved which could be confusing sometimes

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
this graph looks something like

            0
        4       6
    7       5 
  9   3     2
  1
  8
"""