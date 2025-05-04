n = 11
arr = [1,4,-5,12,-1,-2,41,18,31,9,11]
arr.sort()
print(arr)

tosearch = 56

left = 0
right = n-1

while left <= right:
    mid = (left+right)//2
    if arr[mid] == tosearch:
        break
    else:
        if arr[mid] > tosearch:
            #then search on left
            right = mid-1
        else:
            left = mid+1

if left <= right:
    #ie search was complete
    print(mid)
else:
    print("not found")
