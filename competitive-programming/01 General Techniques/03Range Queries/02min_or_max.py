#Brute force O(1) pre and O(N) time
#Sparse table O(nlogn) pre and O(1) time
import math
n = 8
arr = [2,3,4,5,3,1,1,3]

#we will make a table of minimum of the substrings of lengths of power of 2

#sparse_table[startingelement][power that corresponds to size of the substring]

#can be found recursively like

#st[start][power] = min(st[start][power-1],st[start+2^(power-1)][power-1])
#the first half array starts with 'start' only while the second starts with
#doing power-1 for half size

#the outerloop will be of power and inner of the starting point

h = int(math.log(n,2))
sparse_table = [[-1 for _ in range(h+1)] for __ in range(n)]
#base case:
for each in range(n):
    sparse_table[each][0] = arr[each]

#for each power from 1 to log2n (included)
for power in range(1,h+1):
    #for each start that has valid length for that power which will be from 0 ... n-(1<<power) (included)
    for start in range(n-(1<<power)+1):
        sparse_table[start][power] = min(sparse_table[start][power-1], sparse_table[start+(1<<(power-1))][power-1])

print(sparse_table)

def query(left,right):
    length = right-left+1
    k = int(math.log(length,2))
    return min(sparse_table[left][k],sparse_table[right-(1<<k)+1][k])

print(query(1,4))
print(query(3,5))
print(query(0,1))