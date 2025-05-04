import sys, math
sys.setrecursionlimit(10**9)
n, k = [int(x) for x in input().split()]
removables = [int(x) for x in input().split()]

memo = [-1 for i in range(k+1)]

def winner(stones):
  if memo[stones] != -1:
    return memo[stones]
  if stones == 0:
    retval = 2
  else:
    #assume second wala le jitxa
    retval = 2
    #if any of the moves lead to second wala jitxa then first wala le jitxa
    for possibility in removables:
      if possibility > stones:
        continue
      if winner(stones-possibility) == 2:
        retval = 1
        break
  memo[stones] = retval
  return retval

if winner(k) == 1:
  print("First")
else:
  print("Second")