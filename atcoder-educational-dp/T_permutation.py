import sys
sys.setrecursionlimit(10**9)
n = int(input())
s = input()

modder = 10**9+7

permus = [[123 for i in range(0,n+1)] for j in range(n)]
#first index is for upto which goes from 0 to n-1
#second index is for last digit which goes from 1 to n (so gotta make from 0 to n)

for upto in range(n):
  if upto != 0:
    prefix_sum = [-1 for i in range(n+1)]
    prefix_sum[1] = permus[upto-1][1]
    for nextt in range(2,n+1):
      prefix_sum[nextt] = prefix_sum[nextt-1]+permus[upto-1][nextt]
  for last_digit in range(1,n+1): #upto+1 samma gaye ni hunthyo
  #for last_digit in range(1,upto+1):
    if upto == 0:
      if last_digit == 1:
        final1 = 1
        final2 = 1
      else:
        final2 = 0
        final2 = 0
    else:
      if s[upto-1] == '<':
        L,R = 1,last_digit
      else:
        L,R = last_digit,upto+1
      if L <= R-1:
        final1 = prefix_sum[R-1]
        if L != 1:
          final1 -= prefix_sum[L-1]
      else:
        final1 = 0
      #final2 = sum([permus[upto-1][k] for k in range(L,R)])
    permus[upto][last_digit] = final1%modder
    
totals = [permus[n-1][k] for k in range(1,n+1)]
print(sum(totals)%modder)