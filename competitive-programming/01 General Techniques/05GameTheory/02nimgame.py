#There are n heaps, the players alternatively pick any number of sticks

#so the states are [x0,x1,x2,...,xn-1]
#the losing state is [0,0,0,..,0]
#what are the winning states?

#It's found that those states whose nim sum: s = x1 XOR x2 XOR ... xn is zero are the losing states
#Others are winning states

#To find the next move, we make necessary changs so as to make the XOR sum zero

n = 6
heaps = [4,2,1,3,4,6]
nimsum = 0
for each in heaps:
    nimsum = nimsum | each
if nimsum == 0:
    print("First player loses")
else:
    print("Second player loses")
