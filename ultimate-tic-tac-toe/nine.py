import random
import math
import copy
import time

PINF =  1e6
NINF = -1e6

class GameState:
    MAX = 'X'
    MIN = 'O'

    MAX_POINT =  6*1e5
    MIN_POINT = -6*1e5

    DRAW_POINT = 0

    DEPTH = 1
    TIME_FOR_MCTS = 1

    def __init__(self, board, player):
        self.board  = board
        self.player = player

    # As the name says
    def print_board(self):
        for row_board in self.board:
            for small_board in row_board:
                for x in small_board:
                    print(x)
                print("---------------")

        wins_in_each_board = [
            [None, None, None],
            [None, None, None],
            [None, None, None],
        ]
        for i in range(3):
            for j in range(3):
                wins_in_each_board[i][j] = self.terminal_of_ij(i,j)
        for row in wins_in_each_board:
            print(row)

    # Checks terminal value of board(i,j); 
    # 1 for x win, -1 for o win, 0 for loss and None for game not finished
    def terminal_of_ij(self, i, j):
        each_board = self.board[i][j]
        # Row wins:
        for row in each_board:
            if row[0] == row[1] == row[2]:
                winner = row[0]
                if winner == GameState.MAX:
                    return GameState.MAX_POINT
                if winner == GameState.MIN:
                    return GameState.MIN_POINT

        # Col wins:
        for col in range(3):
            if each_board[0][col] == each_board[1][col] == each_board[2][col]:
                winner = each_board[0][col]
                if winner == GameState.MAX:
                    return GameState.MAX_POINT
                if winner == GameState.MIN:
                    return GameState.MIN_POINT

        # Diagonal wins:
        if each_board[0][0] == each_board[1][1] == each_board[2][2]:
            winner = each_board[0][0]
            if winner == GameState.MAX:
                return GameState.MAX_POINT
            if winner == GameState.MIN:
                return GameState.MIN_POINT
        if each_board[0][2] == each_board[1][1] == each_board[2][0]:
            winner = each_board[2][0]
            if winner == GameState.MAX:
                return GameState.MAX_POINT
            if winner == GameState.MIN:
                return GameState.MIN_POINT

        draw = True
        for row in each_board:
            if '?' in row:
                draw = False
                break
        if draw:
            return GameState.DRAW_POINT

        return None

    # Terminal value for whole board, same convention
    def terminal_value(self):
        wins_in_each_board = [
            [None, None, None],
            [None, None, None],
            [None, None, None],
        ]

        # CHECK WINNER IN EACH BOARD:

        for i in range(3):
            for j in range(3):
                wins_in_each_board[i][j] = self.terminal_of_ij(i,j)

        # CHECK FOR OVERALL WINNER:

        # Row wins:
        for row in wins_in_each_board:
            if row[0] == row[1] == row[2]:
                winner = row[0]
                if winner == GameState.MAX_POINT or winner == GameState.MIN_POINT:
                    return winner
                
        # Column wins:
        for col in range(3):
            if wins_in_each_board[0][col] == wins_in_each_board[1][col] == wins_in_each_board[2][col]:
                winner = wins_in_each_board[0][col]
                if winner == GameState.MAX_POINT or winner == GameState.MIN_POINT:
                    return winner

        # Diagonal wins:
        if wins_in_each_board[0][0] == wins_in_each_board[1][1] == wins_in_each_board[2][2]:
            winner = wins_in_each_board[0][0]
            if winner == GameState.MAX_POINT or winner == GameState.MIN_POINT:
                return winner
        if wins_in_each_board[0][2] == wins_in_each_board[1][1] == wins_in_each_board[2][0]:
            winner = wins_in_each_board[2][0]
            if winner == GameState.MAX_POINT or winner == GameState.MIN_POINT:
                return winner

        # Game is not finished yet
        for row in wins_in_each_board:
            if None in row:
                return None

        # Drawn:
        return GameState.DRAW_POINT

    # Legals moves of the current board on self
    def get_legal_moves(self):
        possible_moves = []
        for i in range(3):
            for j in range(3):
                if self.terminal_of_ij(i,j) != None:
                    continue
                board_in_check = self.board[i][j]
                for ii in range(3):
                    for jj in range(3):
                        if board_in_check[ii][jj] == '?':
                            possible_moves.append((i,j,ii,jj))
        return possible_moves

    # Changes the state of the self board until some result
    def random_play(self):
        while self.terminal_value() == None:
            valid_moves = self.get_legal_moves()
            move = random.choice(valid_moves)
            if self.player == GameState.MAX:
                self.board[move[0]][move[1]][move[2]][move[3]] = GameState.MAX
                self.player = GameState.MIN
            elif self.player == GameState.MIN:
                self.board[move[0]][move[1]][move[2]][move[3]] = GameState.MIN
                self.player = GameState.MAX
        return self.terminal_value()

    # how good is the current position?
    def static_evaluation(self):
        evaluation = [
            [None, None, None],
            [None, None, None],
            [None, None, None],
        ]

        for i in range(3):
            for j in range(3):
                each_board = self.board[i][j]
                if self.terminal_of_ij(i,j) != None:
                    evaluation[i][j] = self.terminal_of_ij(i,j)//6
                    continue
                max_count = 0
                min_count = 0
                for row in each_board:
                    if GameState.MIN not in row:
                        max_count += 1
                    if GameState.MAX not in row:
                        min_count += 1
                
                for col in range(3):
                    if each_board[0][col] != GameState.MIN and each_board[1][col] != GameState.MIN and each_board[2][col] != GameState.MIN:
                        max_count += 1
                    if each_board[0][col] != GameState.MAX and each_board[1][col] != GameState.MAX and each_board[2][col] != GameState.MAX:
                        min_count += 1
                        
                if each_board[0][0] != GameState.MIN and each_board[1][1] != GameState.MIN and each_board[2][2] != GameState.MIN:
                    max_count += 1
                if each_board[0][0] != GameState.MAX and each_board[1][1] != GameState.MAX and each_board[2][2] != GameState.MAX:
                    min_count += 1     
                    
                if each_board[0][2] != GameState.MIN and each_board[1][1] != GameState.MIN and each_board[2][0] != GameState.MIN:
                    max_count += 1
                if each_board[0][2] != GameState.MAX and each_board[1][1] != GameState.MAX and each_board[2][0] != GameState.MAX:
                    min_count += 1             
                    
                evaluation[i][j] = max_count - min_count

        totality = 0
        for row in evaluation:
            for each in row:
                totality += each
        return totality

    # returns the game value according to minimax
    def game_value(self, alpha=NINF, beta=PINF, depth=0):
        
        if self.terminal_value() != None:
            return self.terminal_value()
        if depth == GameState.DEPTH:
            return self.static_evaluation()
        
        possible_moves = self.get_legal_moves()
        for move in possible_moves:
            if self.player == GameState.MAX:
                self.board[move[0]][move[1]][move[2]][move[3]] = GameState.MAX
                self.player = GameState.MIN
                alpha = max(alpha, self.game_value(alpha, beta, depth+1))
                self.board[move[0]][move[1]][move[2]][move[3]] = '?'
                self.player = GameState.MAX
                if alpha >= beta:
                    return beta
            else:
                self.board[move[0]][move[1]][move[2]][move[3]] = GameState.MIN
                self.player = GameState.MAX
                beta = min(beta, self.game_value(alpha, beta, depth+1))
                self.board[move[0]][move[1]][move[2]][move[3]] = '?'
                self.player = GameState.MIN
                if beta <= alpha:
                    return alpha
                                                
        if self.player == GameState.MAX:
            return alpha
        elif self.player == GameState.MIN:
            return beta
    
    # returns best move according to minimax
    def minimax(self):
        valid_moves = self.get_legal_moves()
        scores = {}
        for move in valid_moves:
            if self.player == GameState.MAX:
                self.board[move[0]][move[1]][move[2]][move[3]] = GameState.MAX
                self.player = GameState.MIN
            elif self.player == GameState.MIN:
                self.board[move[0]][move[1]][move[2]][move[3]] = GameState.MIN
                self.player = GameState.MAX
            scores[move] = self.game_value()
            self.board[move[0]][move[1]][move[2]][move[3]] = '?'
            if self.player == GameState.MAX:
                self.player = GameState.MIN
            elif self.player == GameState.MIN:
                self.player = GameState.MAX
        if self.player == GameState.MAX:
            maxx = max(scores.items(), key = lambda x : x[1])
        else:
            maxx = min(scores.items(), key = lambda x : x[1])
        return maxx[0]

    # adds information parent, children and scores to the gamestate for mcts
    def make_tree_node(self, parent):
        self.parent = parent
        self.children = {}
        self.visits = 0
        self.draws = 0
        self.x_wins = 0
        self.o_wins = 0

    # returns the best move according to mcts in given time
    def mcts(self, allocated_time):
        self.make_tree_node(None)
        start = time.time()
        ITERATIONS = 0
        while True:
            ITERATIONS += 1
            now = time.time()
            if (now-start) > allocated_time:
                break

            #selection
            play_top = self
            while play_top.terminal_value() == None:
                if len(play_top.get_legal_moves()) != len(play_top.children):
                    break
                best_value = NINF 
                for child_state in play_top.children.values():
                    if play_top.player == GameState.MAX:
                        exploitation = (child_state.x_wins-child_state.o_wins)/child_state.visits
                        exploration = math.sqrt(2*math.log(play_top.visits)/child_state.visits)
                        new_ucb = exploitation + exploration
                    else:
                        exploitation = (child_state.o_wins-child_state.x_wins)/child_state.visits
                        exploration = math.sqrt(2*math.log(play_top.visits)/child_state.visits)
                        new_ucb = exploitation + exploration
                    if new_ucb > best_value:
                        best_value = new_ucb
                        best_child = child_state 
                play_top = best_child

            #expansion
            while True:
                move = random.choice(play_top.get_legal_moves())
                if move in play_top.children:
                    continue
                else:
                    break
            new_play_board = copy.deepcopy(play_top.board)
            if play_top.player == GameState.MAX:
                new_play_board[move[0]][move[1]][move[2]][move[3]] = GameState.MAX
                new_play_top = GameState(new_play_board, GameState.MIN)
            elif play_top.player == GameState.MIN:
                new_play_board[move[0]][move[1]][move[2]][move[3]] = GameState.MIN
                new_play_top = GameState(new_play_board, GameState.MAX)
            new_play_top.make_tree_node(play_top)
            play_top.children[move] = new_play_top
            play_top = new_play_top

            #simulation:
            temp_state = copy.deepcopy(play_top)
            play_top_result = temp_state.random_play()

            #backpropagation:
            while play_top is not None:
                play_top.visits += 1
                if play_top_result == GameState.MAX_POINT:
                    play_top.x_wins += 1
                elif play_top_result == GameState.MIN_POINT:
                    play_top.o_wins += 1
                else:
                    play_top.draws += 1
                play_top = play_top.parent

        scores = {}
        for moves, states in self.children.items():
            scores[moves] = states.visits
        # print("Total iterations is", ITERATIONS)
        if self.player == GameState.MAX:
            maxx = max(scores.items(), key = lambda x : x[1])
        else:
            maxx = min(scores.items(), key = lambda x : x[1])
        return maxx[0]

import pygame, os

pygame.init()
HEIGHT = WIDTH = 600
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Ultimate TIC TAC TOE!")
WHITE = (255,255,255)
BLUE = (0,0,255)
FPS = 60
SIZE_OF_CROSS = (40,40)
BOARD = pygame.image.load(os.path.join('index.png')) 
BOARD = pygame.transform.scale(BOARD, (WIDTH, HEIGHT))
X_IMAGE = pygame.image.load(os.path.join('x_image.png'))
X_IMAGE = pygame.transform.scale(X_IMAGE, SIZE_OF_CROSS)
O_IMAGE = pygame.image.load(os.path.join('o_image.png'))
O_IMAGE = pygame.transform.scale(O_IMAGE, SIZE_OF_CROSS)

BIG_SIZE = (200,200)
BIG_X = pygame.image.load(os.path.join('x_image.png'))
BIG_X = pygame.transform.scale(BIG_X, BIG_SIZE)
BIG_O = pygame.image.load(os.path.join('o_image.png'))
BIG_O = pygame.transform.scale(BIG_O, BIG_SIZE)


OFFSET = 10
BOARD11_X, BOARD11_Y = OFFSET,              OFFSET
BOARD12_X, BOARD12_Y = OFFSET+HEIGHT//3,    OFFSET
BOARD13_X, BOARD13_Y = OFFSET+2*HEIGHT//3,  OFFSET

BOARD21_X, BOARD21_Y = OFFSET,              OFFSET+HEIGHT//3
BOARD22_X, BOARD22_Y = OFFSET+HEIGHT//3,    OFFSET+HEIGHT//3
BOARD23_X, BOARD23_Y = OFFSET+2*HEIGHT//3,  OFFSET+HEIGHT//3

BOARD31_X, BOARD31_Y = OFFSET,              OFFSET+2*HEIGHT//3
BOARD32_X, BOARD32_Y = OFFSET+HEIGHT//3,    OFFSET+2*HEIGHT//3
BOARD33_X, BOARD33_Y = OFFSET+2*HEIGHT//3,  OFFSET+2*HEIGHT//3

BOARD_X = [ 
            [BOARD11_X, BOARD12_X, BOARD13_X], 
            [BOARD21_X, BOARD22_X, BOARD23_X], 
            [BOARD31_X, BOARD32_X, BOARD33_X]
        ] 

BOARD_Y = [ 
            [BOARD11_Y, BOARD12_Y, BOARD13_Y], 
            [BOARD21_Y, BOARD22_Y, BOARD23_Y], 
            [BOARD31_Y, BOARD32_Y, BOARD33_Y]
        ] 

X_OFFSET = 64
Y_OFFSET = 64

font = pygame.font.Font('freesansbold.ttf', 22)
PROMPT_X = font.render('CHOOSE PLAYER X:  (M | T | H)', True, BLUE)
PROMPT_O = font.render('CHOOSE PLAYER O:  (M | T | H)', True, BLUE)

def draw_window(game):
    WIN.blit(BOARD, (0,0))
    for i in range(3):
        for j in range(3):
            each_board = game.board[i][j]
            for row in range(3):
                for col in range(3):
                    if each_board[row][col] == game.MAX:
                        WIN.blit(X_IMAGE, (BOARD_X[i][j]+X_OFFSET*col, BOARD_Y[i][j]+Y_OFFSET*row))
                    if each_board[row][col] == game.MIN:
                        WIN.blit(O_IMAGE, (BOARD_X[i][j]+X_OFFSET*col, BOARD_Y[i][j]+Y_OFFSET*row))

            BIG_OFFSET = 200
            if game.terminal_of_ij(i,j) == GameState.MAX_POINT:
                WIN.blit(BIG_X, (BIG_OFFSET*j, BIG_OFFSET*i))
            elif game.terminal_of_ij(i,j) == GameState.MIN_POINT:
                WIN.blit(BIG_O, (BIG_OFFSET*j, BIG_OFFSET*i))

    pygame.display.update()


def main():
    clock = pygame.time.Clock()

    board = [
                # row1
                [
                    #(row1, col1)
                    [
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ],
                    #(row1, col2)
                    [
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ],
                    #(row1, col3)
                    [
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ]
                ],
                # row2
                [
                    #(row2, col1)
                    [
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ],
                    #(row2, col2)
                    [
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ],
                    #(row2, col3)
                    [
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ]
                ],
                # row3
                [
                    #(row3, col1)
                    [
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ],
                    #(row3, col2)
                    [
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ],
                    #(row3, col3)
                    [
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ['?', '?', '?'],
                    ]
                ],
            ]
    game = GameState(board, 'X')
    WIN.fill(WHITE)
    WIN.blit(PROMPT_X, (HEIGHT//2-150, HEIGHT//2))
    pygame.display.update()
    while True:
        done = False
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_m:
                    PlayerX = 'M'
                    done = True
                if event.key == pygame.K_t:
                    PlayerX = 'T'
                    done = True
                if event.key == pygame.K_h:
                    PlayerX = 'H'
                    done = True
        if done:
            break
    print("Player X is: ", PlayerX)

    WIN.fill(WHITE)
    WIN.blit(PROMPT_O, (HEIGHT//2-150, HEIGHT//2))
    pygame.display.update()
    while True:
        done = False
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_m:
                    PlayerO = 'M'
                    done = True
                if event.key == pygame.K_t:
                    PlayerO = 'T'
                    done = True
                if event.key == pygame.K_h:
                    PlayerO = 'H'
                    done = True
        if done:
            break
    print("Player O is: ", PlayerO)
    draw_window(game)

    while True:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()

        ##################### X's TURN ####################
        match PlayerX:
            case 'H':
                pass
            case 'M':
                best_move = game.minimax()
            case 'T':
                best_move = game.mcts(GameState.TIME_FOR_MCTS)

        game.board[best_move[0]][best_move[1]][best_move[2]][best_move[3]] = GameState.MAX
        game.player = GameState.MIN
        if game.terminal_value() != None:
            break
        draw_window(game)
        ##################### O's TURN ####################
        match PlayerO:
            case 'H':
                pass
            case 'M':
                best_move = game.minimax()
            case 'T':
                best_move = game.mcts(GameState.TIME_FOR_MCTS)
        game.board[best_move[0]][best_move[1]][best_move[2]][best_move[3]] = GameState.MIN
        game.player = GameState.MAX
        if game.terminal_value() != None:
            break
        draw_window(game)
        ###################################################

    while True:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
        draw_window(game)

if __name__ == '__main__':
    main()