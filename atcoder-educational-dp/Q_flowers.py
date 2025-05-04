import sys
sys.setrecursionlimit(10**9)
n = int(input())
heights = [int(x) for x in input().split()]
beauties = [int(x) for x in input().split()]

#segment tree for flowers
INF = 0
base = 1
while (base < n):
  base *= 2
segment_tree = [0]*(2*base-1)

#first draft: flowers = [0 for _ in range(n)]

#second draft: 
flowers = [0 for _ in range(n+1)]


#make tree that corresponds to the subarray starting beg..end
def construcTree(beg=0, end=n-1, root=0):
  if beg == end:
    segment_tree[root] = flowers[beg]
  else:
    mid = (beg+end)//2
    #make left subtree
    construcTree(beg, mid, 2*root+1)
    #make right subtree
    construcTree(mid+1, end, 2*root+2)
    #put value into the root by taking minimum of left and right root
    segment_tree[root] = max(segment_tree[2*root+1],segment_tree[2*root+2])

#update tree that corresponds to the subarray starting beg..end
#flowers ko pos ma change aayo bro do check it out and update it
def updateTree(pos, beg=0, end=n-1, root=0):
  if beg == end:
    segment_tree[root] = flowers[pos]
  else:
    mid = (beg+end)//2
    #if the pos of update is on the left than the middle value
    if pos <= mid:
    	#then update the left tree
        updateTree(pos, beg, mid, 2*root+1);
    else:
    	#else update the right tree
        updateTree(pos, mid+1, end, 2*root+2);
    segment_tree[root] = max(segment_tree[2*root+1],segment_tree[2*root+2])
    
def query(qbeg, qend, beg=0, end=n-1, root=0):
  #total overlap
  if qbeg <= beg and qend >= end:
    return segment_tree[root]
  #no overlap
  if qbeg > end or qend < beg:
    return 0
  #partial overlap
  mid = (beg+end)//2
  return max(query(qbeg,qend,beg,mid,2*root+1),query(qbeg,qend,mid+1,end,2*root+2))

"""
flowers[0] = beauties[0]
for upto in range(1,n):
  maxval = 0
  for each_flower in range(upto):
    if heights[each_flower] < heights[upto]:
      maxval = max(maxval, flowers[each_flower])
    flowers[upto] = maxval+beauties[upto]
"""

#for flower in range(n):
  #for i in range(heights[flower]):
    #flowers[heights[flower]] = max(flowers[heights[flower]],flowers[i]+beauties[flower])
    
for flower in range(n):
  flowers[heights[flower]] = query(0,heights[flower]-1)+beauties[flower]
  updateTree(heights[flower])
print(max(flowers))
