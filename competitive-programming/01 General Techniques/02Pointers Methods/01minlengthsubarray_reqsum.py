import sys
n = 8
arr = [1,3,2,5,1,1,2,3]
#to find the minimum length subarray whose sum >= required;

#O(n)
subsum = 0
required = 5
left = 0
#we fix the left pointer at 0 in the begniing and only change it when the subarray sum >= required

minlength = sys.maxsize
#this find the sum>=required of minimum length
for right in range(n):
    subsum += arr[right]
    while subsum >= required:
        #here we are dealing with subarray such that the condition is met
        minlength = min(minlength, right-left+1)

        #the order of these statements cant be changed
        subsum -= arr[left]
        left += 1
print("min length is", minlength)


