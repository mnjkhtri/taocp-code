from itertools import product

vertices = 11 #goes from 0 to 9
edges = 10
adj = [[] for _ in range(vertices)]
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  adj[temp[0]].append(temp[1])
  adj[temp[1]].append(temp[0])

#we find the toleaf after we had visited all the children so the piece of code is placed as above
to_leaf = [0 for _ in range(vertices)]
def dfs(current, parent=-1):
    for adjacents in adj[current]:
        if adjacents != parent:
            dfs(adjacents, current)

    for again in adj[current]:
        if again != parent:
            to_leaf[current] = max(to_leaf[current], 1+to_leaf[again])
dfs(0)
print(to_leaf)
#to find the longest length such that the top node is the 'current' we do the dfs again
top_node = [0 for _ in range(vertices)]
def dfsagain(current, parent=-1):
    
    #meaning that it has only one subtee (and also one condition is added to make sure that the node is not the starting node)
    if len(adj[current]) == 2 and parent != -1:
        top_node[current] = to_leaf[current]
    #else it has two or more subtree
    else:
        for first,second in product(adj[current],adj[current]):
            if first == second:
                continue
            if first == parent or second == parent:
                continue
            top_node[current] = max(top_node[current], 2+to_leaf[first]+to_leaf[second])

    for adjacents in adj[current]:
        if adjacents != parent:
            dfsagain(adjacents, current)

dfsagain(0)
print(top_node)
print(max(top_node))
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
8 10
this graph looks something like

            0
        4       6
    7       5 
  9   3     2
  1
  8
  10
"""