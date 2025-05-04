import sys
INF = sys.maxsize
vertices = 4 #goes from 0 to 3
edges = 5
adjmat = [[0 for _ in range(vertices)] for __ in range(vertices)]
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  adjmat[temp[0]][temp[1]] = temp[2]
  adjmat[temp[1]][temp[0]] = temp[2]

#initally dismat will contain the distances that are direct, ie when no other verices are used as intermediate
dismat = [[INF for _ in range(vertices)] for __ in range(vertices)]

for i in range(vertices):
    dismat[i][i] = 0
for row in range(vertices):
    for col in range(vertices):
        if adjmat[row][col]:
            dismat[row][col] = adjmat[row][col]

#now the dismat is updated for each vertex could be used as intermediate
for vertex in range(vertices):
    for row in range(vertices):
        for col in range(vertices):
            dismat[row][col] = min(dismat[row][col], dismat[row][vertex]+dismat[vertex][col])

print(dismat)
"""
0 1
2 3

0 1 3
2 3 10
1 3 3
0 3 10
0 2 1
"""