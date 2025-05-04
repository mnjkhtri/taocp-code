import sys
INF = sys.maxsize

vertices = 5 #goes from 0 to 9
edges = 7
edgelist = []
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  edgelist.append((temp[0],temp[1],temp[2]))
  #edgelist.append((temp[1],temp[0],temp[2]))


print(edgelist)

#to find the shortest path, or to check whether the cycle contains a negative cycle
#by doing it for one extra times, to see if any distances are changed
#O(VE)
distances = [INF for _ in range(vertices)]
def bellman(start):
    distances[start] = 0
    for vertex in range(1,vertices):
        #changed = False
        for edges in edgelist:
            first,second,weight = edges
            #previous_distance = distances[second]
            distances[second] = min(distances[second], distances[first]+weight)
            #if distances[second] != previous_distance:
                #changed = True
        #if changed == False:
            #break

bellman(0)
print(distances)
    

"""
0 1 4 
 2 3


0 1 3
1 4 1
0 2 1
1 2 7
1 3 5
3 4 7
2 3 2
"""