n = int(input())
weights,solidness,values = list(zip(*[[int(x) for x in input().split()] for _ in range(n)]))

def keyfunction(index):
  return weights[index]+solidness[index]

tester = list(range(n))
tester.sort(key=keyfunction)

dp = [0 for _ in range(max(weights)+max(solidness)+1)]
for i in range(n):
  x = tester[i]
  for j in reversed(range(solidness[x]+1)):
    dp[j+weights[x]] = max(dp[j+weights[x]],dp[j]+values[x])
#print(dp)    
print(max(dp))