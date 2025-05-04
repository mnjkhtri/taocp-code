import sys
INF = sys.maxsize

deno = [1,3,4]

INF = 1e+9
memo = {}

def coins(money):
    if money in memo:
        return memo[money]
    if money == 0:
        retval = 0
    else:
        retval = 1+min([coins(money-denos) if money-denos >= 0 else INF for denos in deno])
    memo[money] = retval
    return retval

print(coins(6))
