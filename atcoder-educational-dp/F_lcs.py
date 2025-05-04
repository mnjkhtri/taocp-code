import sys
sys.setrecursionlimit(10**9)
s = input()
t = input()

lens = len(s)
lent = len(t)

subseq = [[-1 for j in range(lent+1)] for i in range(lens+1)]
for i in range(-1,lens):
  for j in range(-1,lent):
    if i == -1 or j == -1:
      retval = 0
    else:
      if s[i] == t[j]:
        retval = subseq[i-1][j-1]+1
      else:
        retval = max(subseq[i][j-1], subseq[i-1][j])
    subseq[i][j] = retval

i = lens-1
j = lent-1
common = ""
while i >= 0 and j >= 0:
  if subseq[i][j] == subseq[i-1][j]:
    i -= 1
  elif subseq[i][j] == subseq[i][j-1]:
    j -= 1
  else:
    common = s[i] + common
    i -= 1
    j -= 1
print(common)