#pointers coming from opposite way

n = 8
arr = [1,3,2,5,1,1,2,3]

required = 7

left = 0
right = n-1

while left < right:
    if arr[left]+arr[right] == required:
        print(left,right)
        break
    else:
        #if the sum is less the left pointer moves
        if arr[left]+arr[right] < required:
            left += 1
        #if the sum is greater the right pointer moves
        else:
            right -= 1
        



