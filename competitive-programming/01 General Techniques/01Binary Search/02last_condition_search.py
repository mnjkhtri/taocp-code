#the key to understanding binary search is to implement the True-false way
#the function should implement at least one True else the search will return the first index itself
#also at least one false so the loop does not run forever
#so True .... False

def imp_func(element):
    if element <= 90:
        return True
    else:
        return False

#gap should be large enough; let it be large so it contains the false statement (in fact it could be any but for complexity issues)
current = 0
gap = 96
while gap >= 1:
    while imp_func(current+gap):
        current += gap
    gap //= 2

print(current)

#note that if the searching range has some limit then we put current+gap < n and imp_func(current+gap)
#in this case the infinite loop will not occur instead returns the last index