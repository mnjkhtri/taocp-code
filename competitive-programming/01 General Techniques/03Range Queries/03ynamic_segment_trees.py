import sys
INF = sys.maxsize
n = 6
arr = [1,2,3,4,5,1]

if n&(n-1) == 0:
    base = n
else:
    base = int("1"+"0"*(len(bin(n))-2),2)

def imp_func(a,b):
    return a+b

#the initializing value does not matter its just to make sure that children = 2*parent wala formula works good when size = 6; also it does not matter in updating the stuff 
#so to construct the tree we could just update the tree with each index

segment_tree = [-109 for _ in range(2*base-1)]

#to make segment tree corresponding to the array beg..end with the root at position 'root', actually the segment tree is for array of size base>=n
def constructTree(beg=0, end=n-1, root=0):
    if beg == end:
        segment_tree[root] = arr[beg]
    else:
        mid = (beg+end)//2
        #make left subtree
        constructTree(beg,mid,2*root+1)
        #make right subtree
        constructTree(mid+1,end,2*root+2)
        #now put the value into root
        segment_tree[root] = imp_func(segment_tree[2*root+1], segment_tree[2*root+2])

#the pos is changed in the 'arr' so update the array correspoding to beg...end with the root of 'root', here the root is guaranteed to change
def updateTree(pos, beg=0, end=n-1, root=0):
  if beg == end:
    segment_tree[root] = arr[pos]
  else:
    mid = (beg+end)//2
    #if the pos of update is on the left than the middle value
    if pos <= mid:
    	#then update the left tree
        updateTree(pos, beg, mid, 2*root+1);
    else:
    	#else update the right tree
        updateTree(pos, mid+1, end, 2*root+2);
    segment_tree[root] = imp_func(segment_tree[2*root+1],segment_tree[2*root+2])

#search the query in range qbeg..qend in the original array
#here beg and end gives the range the root denotes
def query(qbeg, qend, beg=0, end=n-1, root=0):
    #overlap is with respect to the seasrching subarray ie qbeg-qend
  #total overlap = qbeg-qend contains beg-end
  if qbeg <= beg and qend >= end:
    return segment_tree[root]
  #no overlap = disjoint
  if qbeg > end or qend < beg:
    return 0
  #partial overlap = intersection or beg-end contains qbeg-baseqend
  mid = (beg+end)//2
  return imp_func(query(qbeg,qend,beg,mid,2*root+1),query(qbeg,qend,mid+1,end,2*root+2))


updateTree(0)
updateTree(1)
updateTree(2)
updateTree(3)
updateTree(4)
updateTree(5)
print(segment_tree)