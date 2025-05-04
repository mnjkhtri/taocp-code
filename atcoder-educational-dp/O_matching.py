import sys
sys.setrecursionlimit(10**9)
n = int(input())
compatibility = [[int(x) for x in input().split()] for i in range(n)]
modder = 10**9+7

dp = [0 for i in range(1<<n)]
dp[0] = 1
for women_set in range(1<<n):
  men_count = bin(women_set).count("1")
  for each_woman in range(n):
    #i want those woman who are compatible with last men and are not in the current set
    if compatibility[men_count-1][each_woman] and women_set&(1<<each_woman)==0:
      #now i change the dp state obtained by putting those woman into the set
      dp[women_set^(1<<each_woman)] += dp[women_set]
print(dp[(1<<n)-1]%modder)