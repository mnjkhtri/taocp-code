import sys
from queue import PriorityQueue
INF = sys.maxsize
vertices = 4 #goes from 0 to 9
edges = 5
adj = [[] for _ in range(vertices)]
for _ in range(edges):
  temp = [int(x) for x in input().split()]
  adj[temp[0]].append((temp[1],temp[2]))
  adj[temp[1]].append((temp[0],temp[2]))

distances = [INF for _ in range(vertices)]

#we will need a processed array to tell which nodes are relaxed and done
processed = [False for _ in range(vertices)]

def dijsktra(start):
  #we will save the (distance,node) in the queue
  q = PriorityQueue()
  distances[start] = 0
  q.put((0,start))
  while not q.empty():
    #get the shortest node and check if it is relaxed if not then set it to True and process it, i.e. update its adjacent values
    new_node = q.get()[1]
    if processed[new_node]:
      continue
    processed[new_node] = True

    #now update all the adjacnets valeus
    for vertex,weight in adj[new_node]:
      distances[vertex] = min(distances[vertex], distances[new_node]+weight)
      #we will put all the updated distances into the queue so the priority will automatically pick up which one is shortest and to relax now
      q.put((distances[vertex],vertex))


dijsktra(0)
print(distances)
"""
0 1
2 3


0 1 3
2 3 10
1 3 3
0 3 10
0 2 1
"""

#complexity is O(V+E*logE) so useful for large graphs

#Note dijskray greedy sleect the closest vertex that has not been processed to now relat it
#while bellman relaxes all of the edges so we dont know which one is relaxed at all
#means harek choti ma euta ko path length fix hunthyo bellman ma so we needed n-1 iterations