import sys
INF = sys.maxsize

vertices = 5
edges = 7
edgelist = []
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  edgelist.append((temp[0], temp[1], temp[2]))
  #edgelist.append((temp[1], temp[0], temp[2]))


def bellman(vertex, nedge):
    if nedge == 0: #starting from the zero vertex
        if vertex == 0:
            return 0
        else:
            return INF

    savemin = INF
    for edges in edgelist:
        firstvertex,secondvertex,wt = edges
        if firstvertex == vertex:
            savemin = min(savemin, bellman(secondvertex,nedge-1)+wt)
        elif secondvertex == vertex:
            savemin = min(savemin, bellman(firstvertex,nedge-1)+wt)

    return min(bellman(vertex, nedge-1), savemin)

print(bellman(0,edges), bellman(1,edges), bellman(2,edges), bellman(3,edges), bellman(4,edges))




"""
distances = [INF for _ in range(vertices)]
distances[start] = 0

    for vertex in range(1,vertices):
        for edges in edgelist:
            first,second,weight = edges
            distances[second] = min(distances[second], distances[first]+weight)
"""


"""
0 1 3
1 4 1
0 2 1
1 2 7
1 3 5
3 4 7
2 3 2
"""