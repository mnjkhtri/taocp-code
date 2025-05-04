n = 8
arr = [-1,2,4,-3,5,3,-6,2]

#naive
best = 0
for left in range(n):
    for right in range(n):
        sum = 0
        for k in range(left,right+1):
            sum += arr[k]
        best = max(sum,best)
print(best)

#from the left end
best = 0
for left in range(n):
    sum = 0
    for mover in range(left,n):
        sum += arr[mover]
        best = max(sum,best)
print(best)

#kadanes
best = 0
sum = 0
for right in range(n):
    sum = max(arr[right], sum+arr[right])
    best = max(best,sum)

print(best)

