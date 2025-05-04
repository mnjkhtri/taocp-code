import sys, math
sys.setrecursionlimit(10**9)
n = int(input())
elements = [int(x) for x in input().split()]
totalsum = sum(elements)

taro = 0
jiro = 1

#the lists are for the scores taro can achieve when respective of them plays first
#even though the name says jiro first, the scores are not of jiro

taro_first = [[99 for k in range(n)] for j in range(n)]
jiro_first = [[99 for k in range(n)] for j in range(n)]
 
#topological order if increasing j-1 so  
for diff in range(n):
  for i in range(n):
    j = i+diff
    if j > n-1:
      continue
    if i == j:
      taro_first[i][j] = elements[i]
      jiro_first[i][j] = 0
    else:
      taro_first[i][j] = max(elements[i]+jiro_first[i+1][j], elements[j]+jiro_first[i][j-1])
      jiro_first[i][j] = min(taro_first[i+1][j], taro_first[i][j-1])

taropoints = taro_first[0][n-1]
jiropoints = totalsum - taropoints
print(taropoints-jiropoints)