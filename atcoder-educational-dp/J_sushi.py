import sys, math
sys.setrecursionlimit(10**9)
n = int(input())
shushis = [int(x) for x in input().split()]
ones = shushis.count(1)
twos = shushis.count(2)
threes = shushis.count(3)
zeros = 0
#CHEK HE LAS SUB BRO ELSE :YOU BITCH

eval = [[[10 for l in range(n+1)] for k in range(n+1)] for j in range(n+1)]

for l in range(n+1):
  for k in range(n+1):
    for j in range(n+1):
        i = n-j-k-l
        if i < 0:
          continue
        if i == n:
          retval = 0
        else:
          pi = i/n
          pj = j/n
          pk = k/n
          pl = l/n
          retval = 1
          if j > 0:
            retval += pj*eval[j-1][k][l]
          if k > 0:
            retval += pk*eval[j+1][k-1][l]
          if l > 0:
            retval += pl*eval[j][k+1][l-1]
          retval /= 1-pi
        eval[j][k][l] = retval
  
print(eval[ones][twos][threes])