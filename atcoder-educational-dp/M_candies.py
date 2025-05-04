n, k = [int(x) for x in input().split()]
capacity = [int(x) for x in input().split()]
modder = 10**9+7

numbers = [[-1 for j in range(n+1)] for i in range(k+1)]

for candies in range(k+1):
  numbers[candies][-1] = 0
for children in range(-1,n):
  numbers[0][children] = 1
  
for children in range(n):
  sums = [numbers[0][children-1]]
  for candies in range(1,k+1):
    value = (sums[candies-1]+numbers[candies][children-1])%modder
    sums.append(value)
  for candies in range(1,k+1):
    left = candies
    right = candies-capacity[children]-1
    numbers[candies][children] = sums[left]
    if right >= 0:
      numbers[candies][children] = (numbers[candies][children]-sums[right]+modder)%modder
    #retval = numbers[candies-1][children]+numbers[candies][children-1]
    #if candies-1-capacity[children] >= 0:
      #retval -= numbers[candies-1-capacity[children]][children-1]
    #numbers[candies][children] = retval      
print(numbers[k][n-1])