k = input()
d = int(input())
length = len(k)
modder = 10**9+7

holders = [[[1 for tight in range(2)] for sums in range(d)] for pos in range(length)]

for pos in reversed(range(length)):
  for sums in range(d):
    for tight in range(2):
      if pos == length-1:
        total = 0
        if tight == 1:
          limit = int(k[pos])
        else:
          limit = 9
        for i in range(limit+1):
          if i % d == sums:
            total += 1
      else:
        total = 0
        if tight == 1:
          limit = int(k[pos])
          total = sum([holders[pos+1][(sums-each_digit)%d][0 or (each_digit == limit)] for each_digit in range(limit+1)])
        else:
          limit = 9
          total = sum([holders[pos+1][(sums-each_digit)%d][0] for each_digit in range(limit+1)])
      holders[pos][sums][tight] = total%modder
answer = holders[0][0][1]-1
print(answer%modder)