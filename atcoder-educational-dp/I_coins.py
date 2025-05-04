import sys, math
sys.setrecursionlimit(10**9)
n = int(input())
probs = [float(x) for x in input().split()]

headsprob = [[0.0 for j in range(n+1)] for i in range(n+1)]
for tossno in range(-1,n):
  for nheads in range(n+1):
    if tossno == -1:
      if nheads == 0:
        retval = 1
      else:
        retval = 0
    elif nheads == 0:
      retval = headsprob[tossno-1][0]*(1.0-probs[tossno])
    else:
      retval = headsprob[tossno-1][nheads-1]*probs[tossno]+headsprob[tossno-1][nheads]*(1-probs[tossno])
    headsprob[tossno][nheads] = retval
 
total = 0
half = n//2+1
for i in range(half,n+1):
	total += headsprob[n-1][i]
print(total)