import math
n = int(input())
h = [int(x) for x in input().split()]
h.insert(0,0)
M = [math.inf]*(n+1)
M[1] = 0
for i in range(1,n+1):
    if i+1 <= n:
        M[i+1] = min(M[i+1], M[i]+abs(h[i+1]-h[i]))
    if i+2 <= n:
        M[i+2] = min(M[i+2], M[i]+abs(h[i+2]-h[i]))
print(M[n])