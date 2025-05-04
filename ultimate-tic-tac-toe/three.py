import math
import random
import copy
import time

PINF =  math.inf
NINF = -math.inf

class GameState:
    MAX_POINT =  1
    MIN_POINT = -1
    DRAW_POINT = 0
    
    MIN = 'O'
    MAX = 'X'
    
    ITERATIONS = 100
    MCTS_ITER = 1000
    
    def __init__(self, board, player):
        self.board = board
        self.player = player

    # adds information parent, children and scores to the gamestate for mcts
    def make_tree_node(self, parent):
        self.parent = parent
        self.children = {}
        self.visits = 0
        self.draws = 0
        self.x_wins = 0
        self.o_wins = 0
  
    # shows board in pretty format
    def show_board(self):
        for row in self.board:
            print(row)
        print("---------------")

    # displays root information
    def root_info(self):
        print("Root:", self.visits, "=", self.x_wins, self.o_wins, self.draws)
        for moves,childs in self.children.items():
            print(moves, childs.visits, "=", childs.x_wins, childs.o_wins, childs.draws)

    # returns (whether terminal, terminal value)
    def is_terminal(self):
        # Row wins:
        for row in self.board:
            if row[0] == row[1] == row[2]:
                winner = row[0]
                if winner == GameState.MIN:
                    return True,GameState.MIN_POINT
                if winner == GameState.MAX:
                    return True,GameState.MAX_POINT
                
        # Column wins:
        for col in range(3):
            if self.board[0][col] == self.board[1][col] == self.board[2][col]:
                winner = self.board[0][col]
                if winner == GameState.MIN:
                    return True,GameState.MIN_POINT
                if winner == GameState.MAX:
                    return True,GameState.MAX_POINT

        # Diagonal wins:
        if self.board[0][0] == self.board[1][1] == self.board[2][2]:
            winner = self.board[0][0]
            if winner == GameState.MIN:
                return True,GameState.MIN_POINT
            if winner == GameState.MAX:
                return True,GameState.MAX_POINT
        if self.board[0][2] == self.board[1][1] == self.board[2][0]:
            winner = self.board[2][0]
            if winner == GameState.MIN:
                return True,GameState.MIN_POINT
            if winner == GameState.MAX:
                return True,GameState.MAX_POINT

        # Draws
        draw = True
        for row in self.board:
            if ' ' in row:
                draw = False
                break
        if draw:
            return True,GameState.DRAW_POINT
    
        return False,None

    # returns (list of possible values)
    def possible_moves(self):
        possibles = [] 
        for row in range(3):
            for col in range(3):
                if self.board[row][col] == ' ':
                    possibles.append((row,col))
        return possibles

    # returns (result of a random game); make copy of the state before playing a random game
    def random_play(self):
        while True:
            whether, value = self.is_terminal()
            if whether == True:
                return value
            possible_moves = []
            for row in range(3):
                for col in range(3):
                    if self.board[row][col] == ' ':
                        possible_moves.append((row,col))
            idx = random.choice(possible_moves)
            if self.player == GameState.MAX:
                self.board[idx[0]][idx[1]] = GameState.MAX
                self.player = GameState.MIN
            else:
                self.board[idx[0]][idx[1]] = GameState.MIN
                self.player = GameState.MAX
            
    # returns (game value)
    def game_value(self, alpha=NINF, beta=PINF):
        
        whether, value = self.is_terminal()
        if whether:
            return value
        
        for row in range(3):
            for col in range(3):
                if self.board[row][col] == ' ':
                    if self.player == GameState.MAX:
                        self.board[row][col] = GameState.MAX
                        self.player = GameState.MIN
                        alpha = max(alpha, self.game_value(alpha, beta))
                        self.board[row][col] = ' '
                        self.player = GameState.MAX
                        if alpha >= beta:
                            return beta
                    else:
                        self.board[row][col] = GameState.MIN
                        self.player = GameState.MAX
                        beta = min(beta, self.game_value(alpha, beta))
                        self.board[row][col] = ' '
                        self.player = GameState.MIN
                        if beta <= alpha:
                            return alpha
                                                
        # return best_value
        if self.player == GameState.MAX:
            return alpha
        else:
            return beta
    
    # returns (heuristic value)
    def static_evaluation(self):
        max_count = 0
        min_count = 0
        for row in self.board:
            if GameState.MIN not in row:
                max_count += 1
            if GameState.MAX not in row:
                min_count += 1
        
        for col in range(3):
            if self.board[0][col] != GameState.MIN and self.board[1][col] != GameState.MIN and self.board[2][col] != GameState.MIN:
                max_count += 1
            if self.board[0][col] != GameState.MAX and self.board[1][col] != GameState.MAX and self.board[2][col] != GameState.MAX:
                min_count += 1
                
        if self.board[0][0] != GameState.MIN and self.board[1][1] != GameState.MIN and self.board[2][2] != GameState.MIN:
            max_count += 1
        if self.board[0][0] != GameState.MAX and self.board[1][1] != GameState.MAX and self.board[2][2] != GameState.MAX:
            min_count += 1     
            
        if self.board[0][2] != GameState.MIN and self.board[1][1] != GameState.MIN and self.board[2][0] != GameState.MIN:
            max_count += 1
        if self.board[0][2] != GameState.MAX and self.board[1][1] != GameState.MAX and self.board[2][0] != GameState.MAX:
            min_count += 1             
            
        return max_count - min_count
        self.board[row][col] = player
    
    # returns (expected value of many random games)
    def expected_value(self):
        expected_sum = 0
        iterations = GameState.ITERATIONS
        for _ in range(iterations):
            new_game = copy.deepcopy(self)
            expected_sum += new_game.random_play()
            # del new_game
        return expected_sum/iterations
        
    # returns (x_win-o_win of many random games)
    def monte_carlo(self):
        x_wins = 0
        o_wins = 0
        draws = 0
        iterations = GameState.ITERATIONS
        for _ in range(iterations):
            new_game = copy.deepcopy(self)
            result = new_game.random_play()
            if result == GameState.MAX_POINT:
                x_wins += 1
            elif result == GameState.MIN_POINT:
                o_wins += 1
            else:
                draws += 1
        return x_wins - o_wins     
        
    # returns (best move of the game based on measure func)
    def best_mover(self, func):
        best_move = (-1,-1)
        if self.player == GameState.MAX:
            best_value = NINF
        else:
            best_value = PINF
            
        for row in range(3):
            for col in range(3):
                if self.board[row][col] == ' ':
                    if self.player == GameState.MAX:
                        self.board[row][col] = GameState.MAX
                        self.player = GameState.MIN
                        new_value = func(self);
                        if new_value > best_value:
                            best_value = new_value
                            best_move = (row,col)
                        self.board[row][col] = ' '
                        self.player = GameState.MAX
                    else:
                        self.board[row][col] = GameState.MIN
                        self.player = GameState.MAX
                        new_value = func(self);
                        if new_value < best_value:
                            best_value = new_value
                            best_move = (row,col)
                        self.board[row][col] = ' '
                        self.player = GameState.MIN
        return best_move

    # returns (best move on mcts iterations)
    def mcts(self, limit=None):
        self.make_tree_node(None)
        start = time.time()
        for _ in range(GameState.MCTS_ITER):
            now = time.time()
            if limit is not None:
                if (now-start) > limit:
                    break
            play_top = self
            while not play_top.is_terminal()[0]:
                if len(play_top.possible_moves()) == len(play_top.children):
                    best_value = NINF 
                    for child_state in play_top.children.values():
                        if play_top.player == GameState.MAX:
                            exploitation = (child_state.x_wins-child_state.o_wins)/child_state.visits
                            exploration = 2*math.sqrt(math.log(play_top.visits)/child_state.visits)
                            new_ucb = exploitation + exploration
                        else:
                            exploitation = (child_state.o_wins-child_state.x_wins)/child_state.visits
                            exploration = 2*math.sqrt(math.log(play_top.visits)/child_state.visits)
                            new_ucb = exploitation + exploration
                        if new_ucb > best_value:
                            best_value = new_ucb
                            best_child = child_state 
                    play_top = best_child 
                else:
                    while True:
                        move = random.choice(play_top.possible_moves())
                        if move in play_top.children:
                            continue
                        else:
                            break
                    new_play_board = copy.deepcopy(play_top.board)
                    if play_top.player == GameState.MAX:
                        new_play_board[move[0]][move[1]] = GameState.MAX
                        new_play_top = GameState(new_play_board, GameState.MIN)
                    else:
                        new_play_board[move[0]][move[1]] = GameState.MIN
                        new_play_top = GameState(new_play_board, GameState.MAX)
                    new_play_top.make_tree_node(play_top)
                    play_top.children[move] = new_play_top
                    play_top = new_play_top
                    break
            # Here play top is the node from which we got to simulate our game
            temp_board = copy.deepcopy(play_top.board)
            temp_state = GameState(temp_board, play_top.player)
            play_top_result = temp_state.random_play()            
            # Now backpropagate from the play-top node
            while play_top is not None:
                play_top.visits += 1
                if play_top_result == GameState.MAX_POINT:
                    play_top.x_wins += 1
                elif play_top_result == GameState.MIN_POINT:
                    play_top.o_wins += 1
                else:
                    play_top.draws += 1
                play_top = play_top.parent

        best_value = NINF
        for moves, states in self.children.items():
            new_value = states.visits
            if new_value > best_value:
                best_value = new_value
                best_move = moves
        return best_move

def main(): 
    x_time = 0
    o_time = 0
    board = [
            [' ', ' ', ' '],
            [' ', ' ', ' '],
            [' ', ' ', ' ']
                            ]
    game = GameState(board, 'X')
    while True:
        # FIRST PLAYER:
        whether, value = game.is_terminal()
        if whether:
            if value == GameState.MAX_POINT:
                print("X wins")
            elif value == GameState.MIN_POINT:
                print("O wins")
            else:
                print("Nobody wins")
            break
        start = time.time()
        make_move = game.mcts(0.1)
        # make_move = game.best_mover(GameState.game_value())
        end = time.time()
        x_time += (end-start)
        formatted_time = "{:.5f}".format(end-start)
        print("Time elased to make X:", formatted_time)        
        game.board[make_move[0]][make_move[1]] = 'X'
        game.player = 'O'
        game.show_board()

        # SECOND PLAYER:
        whether, value = game.is_terminal()
        if whether:
            if value == GameState.MAX_POINT:
                print("X wins")
            elif value == GameState.MIN_POINT:
                print("O wins")
            else:
                print("Nobody wins")
            break
        start = time.time()
        make_move = game.mcts()
        # make_move = game.best_mover(GameState.monte_carlo)
        end = time.time()
        o_time = (end-start)
        formatted_time = "{:.5f}".format(end-start)
        print("Time elased to make O:", formatted_time)
        game.board[make_move[0]][make_move[1]] = 'O'
        game.player = 'X'
        game.show_board()
    print(" ")
    print("--- TIMING ---")
    print("X took", "{:.5f}".format(x_time))
    print("O took", "{:.5f}".format(o_time))

main()