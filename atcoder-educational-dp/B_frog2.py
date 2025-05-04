import math
t = input().split()
n,k = t
n = int(n)
k = int(k)

h = [int(x) for x in input().split()]
h.insert(0,0)

M = [math.inf]*(n+1)
M[1] = 0
for i in range(1,n+1):
  for j in range(i+1,i+k+1):
    if (j <= n):
        M[j] = min(M[j],M[i]+abs(h[j]-h[i]))
print(M[n])