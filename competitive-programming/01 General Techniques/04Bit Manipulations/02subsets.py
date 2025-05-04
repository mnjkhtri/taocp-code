#to iterate the subsets of an array of size n
#we go from 0 to 2**n-1

#how about subset of a particular set represented in that very way?

x = 12
print(bin(x))
#to process the subsets of x

#first way: (start from the full subset and go on to empty)
b = x
while b > 0:
    print(bin(b),b)
    b = (b-1)&x
print(bin(b),b)
#wherever the print statements are there, do the thing

#second way: (starts from emtpy and goes on to full)
b = 0
print(bin(b),b)
b = (b-x)&x
while b > 0:
    print(bin(b),b)
    b = (b-x)&x