#to find element at position k after sorting the array
#to find kth largest or smallest element
import random

n = 10
testlist = list(range(5,15))
testlist = [41,100,71,15,22,81,19,10,61,45]

#note order will start like 0th, 1th ... (n-1)th value
def orderstatistic(left,right,order):
    pos = random.randint(left,right)    #left and right are inclusive
    value = testlist[pos]
    i = left
    j = right
    #we will put the value at 'pos' in its appropriate position such that left elemlents are smaller and right elements are larger
    #the new position where it will be placed will be left=right, then we will check if that new positon == order then we are done
    #else we will search at left or right array
    while i < j:
        while testlist[i] < value:
            i += 1
        while testlist[j] > value:
            j -= 1
        #exchange the elements at left and right positins
        temp = testlist[i]
        testlist[i] = testlist[j]
        testlist[j] = temp
    newpos = i
    #the newpos is the absolute index while the order is the index with respect to the left boundary (hence relative)
    #we cannot compare absolute and relative indexes, neither can subtract them for them
    if newpos == order+left:
        return value
    else:
        #if the newpos is grater than the required order then we have to search in the left part
        if newpos > order+left:
            #print(left,newpos-1)
            return orderstatistic(left,newpos-1,order)
        else:
            #print(left,newpos-1)
            return orderstatistic(newpos+1,right,order-newpos-1+left)

print(orderstatistic(0,n-1,6))