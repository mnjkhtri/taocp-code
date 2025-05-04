import sys
INF = sys.maxsize
vertices = 4 #goes from 0 to 3
edges = 5
adjmat = [[0 for _ in range(vertices)] for __ in range(vertices)]
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  adjmat[temp[0]][temp[1]] = temp[2]
  adjmat[temp[1]][temp[0]] = temp[2]

#floyd(start,end,permitteds) = shortest path from start to end alloweing the nodes from 0..permitted to be intermediates
def floyd(start,end,permitteds):
    if permitteds == -1: #meaning no vertices are permitted as intermediates
        if start == end:
            return 0
        elif adjmat[start][end]:
            return adjmat[start][end]
        else:
            return INF 
    
    #return mininum of 1)path from start to end with 0..permieeds-1 ..2) use that new permitteds node 
    return min(floyd(start,end,permitteds-1), floyd(start,permitteds,permitteds-1)+floyd(permitteds,end,permitteds-1))

print(floyd(0,3,vertices-1))
print(floyd(0,2,vertices-1))
print(floyd(0,1,vertices-1))
print(floyd(0,0,vertices-1))



"""
0 1
2 3

0 1 3
2 3 10
1 3 3
0 3 10
0 2 1
"""