#when you need a query of sum for q times the complexity will be O(nq)
#but we will take the time O(n) to set up the prefix sum and the queries will be done in O(1)
#so its either O(n) or O(q) whichever is higher 

n = 8
arr = [1,3,4,8,6,1,4,2]
prefix_arr = [0 for _ in range(n)]
prefix_arr[0] = arr[0]

for idx in range(1,n):
    prefix_arr[idx] = prefix_arr[idx-1]+arr[idx]

print(prefix_arr)

#now that the array is set up lets write the code for quering
#to find the sum from 0 to i, prefix_arr[i]

left = 1
right = 2

total = prefix_arr[right]
if left != 0:
    total -= prefix_arr[left-1]

print(total)