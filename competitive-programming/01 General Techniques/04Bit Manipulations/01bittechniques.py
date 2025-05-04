import math

#binval = "1001"
binval = "10101111010110101010100110011"
intval = int(binval,2)
print(intval)
print(binval)
k = 5

#To set the kth bit to 1
toprint = bin(intval|(1<<k))
print(toprint[2:])

#To set the kth bit to 0
toprint = bin(intval&~(1<<k))
print(toprint[2:])

#To set the kth bit to 0
toprint = bin(intval|(1<<k))
print(toprint[2:])

#To remove the rightmost 1
toprint = bin(intval&(intval-1))
print(toprint[2:])
#->To check whether power of 2

#To extract the rightmost 1
toprint = bin(intval&(-intval))
print(toprint[2:])
#->Smallest power of 2 that divides it

#<= n that is power of 2
toprint = math.floor((math.log(intval,2)))
toprint = 2**toprint
print(toprint)

#>=n that is pwoer of 2
if intval&(intval-1) == 0:
    toprint = intval
else:
    toprint = int("1"+"0"*(len(bin(intval))-2),2)
print(toprint)
