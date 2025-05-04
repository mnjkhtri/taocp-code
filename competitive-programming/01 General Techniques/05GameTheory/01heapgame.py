#Player 1 and player 2 move alternatively
#There is a heap of n sticks, the players remove either 1, 2 or 3 sticks alternatively
#If there are 0 sticks left, the current player loses

#so there are the states from 0...n which gives the win-or-lose of the player with current move
#Example
#0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
#L, W, W, W, L, W, W, W, L, W, W

#so if n is divisible by 4, we lose (of course if other play plays optimally)
#also generalizing for k picks up

n = 5
k = 2
if n%k == 0:
    print("The first player loses")
else:
    print("The first player wins")