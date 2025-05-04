deno = [1, 2, 5, 10, 20, 50, 100]
money = 551

#not working case
#deno = [1,3,4]
#money = 6

denoindex = len(deno)-1

count = 0

while denoindex >= 0:
    while deno[denoindex] <= money:
        print(deno[denoindex])
        count += 1
        money -= deno[denoindex]
    denoindex -= 1

print("count is",count)
