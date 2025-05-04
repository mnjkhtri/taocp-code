import sys
n, w = [int(x) for x in input().split()]
W, V = zip(*[[int(x) for x in input().split()] for i in range(n)])

INF = sys.maxsize

knapsac = [[-1 for j in range(sum(V)+1)] for i in range(n+1)]
for i in range(sum(V)+1):
  knapsac[-1][i] = INF
for i in range(n+1):
  knapsac[i][0] = 0

for itemno in range(0,n):
  for value in range(1,sum(V)+1):
    if value >= V[itemno]:
      retval = min(knapsac[itemno-1][value], W[itemno]+knapsac[itemno-1][value-V[itemno]])
    else:
      retval = knapsac[itemno-1][value]
    knapsac[itemno][value] = retval

for eachpossibleval in reversed(range(sum(V)+1)):
  if knapsac[n-1][eachpossibleval] <= w:
    finalval = eachpossibleval
    break
print(finalval)