#backtracking the 8 queens

n = 12
count = 0
column = [0 for _ in range(n)]
diag1 = [0 for _ in range(2*n-1)]
diag2 = [0 for _ in range(2*n-1)]


def queens(row):
    global count
    if row == n:
        count += 1
    else:
        for col in range(n):
            if column[col] or diag1[col+row] or diag2[col-row+n-1]:
                continue
            column[col] = diag1[col+row] = diag2[col-row+n-1] = 1
            queens(row+1)
            column[col] = diag1[col+row] = diag2[col-row+n-1] = 0

queens(0)
print(count)


    