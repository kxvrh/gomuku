import numpy as np

class gomuku_board(object):
    def _init_(self):
        self.width = 19
        self.height = 19
        self.states = {} # key: move, value:player
        self.players = [1, 2] #player1, player2
        self.n = 5 # 5 to win
     
    def init_board(self, start_player=0):
        self.current_player = self.players[start_player]
        self.available_moves = self.width * self.height
        self.states = {}
        self.last_move = -1
        """
        current state
        0 for available moves/unoccupied
        1 for player1
        2 for player2
        """
        self.current_state = np.zeros(self.width * self.height)
    
        
    def location(self, move):
        """
        move in 19x19 board
        342 343 ... 359 360
        .   .       .   .
        .   .       .   .
        38  39  ...  55 56
        19  20  ...  36 37
        0    1  ...  17 18
        """
        row = move // self.width
        col = move % self.width
        return [row, col]
    
    def move(self, location):
        if(len(location)!= 2):
            return -1
        r = location[0]
        c = location[1]
        move = r * width + c
        if(move not in range(self.width * self.height)):
            return -1
        return move
        
    def current_state(self):
        return self.current_state
    
    def current_player(self):
        return self.current_player
    
    def do_move(self, move):
        self.states[move] = self.current_player
        self.current_state[move] = self.current_player   
        self.available_moves.remove(move)
        self.last_move = move
        
    def take_turn(self, current_player):
        if self.current_player == self.players[0]:
            self.current_player = self.player[1]
        else:
             self.current_player = self.player[0]
        
    def winner(self):
        width = self.width
        height = self.height
        occupied = list(set(range(width * height)) - set(self.available_moves))
        
        for o in occupied:
            r, c = self.location(o)
            player = self.current_state[o]
            
            if r + self.n - 1 < width and c + self.n -1 < height:
                for i in range(self.n):
                    if current_state[o + i] != player:
                        break
                    if i = self.n - 1:
                        return True, player
                
                for i in range(self.n):
                    if current_state[o + 19 * i] != player:
                        break
                    if i = self.n - 1:
                        return True, player
                
                for i in range(self.n):
                    if current_state[o + 20 * i] != player:
                        break
                    if i = self.n - 1:
                        return True, player
                    
                if current_state[o - 18 * i] != player:
                        break
                    if i = self.n - 1:
                        return True, player
        return False, -1

    def game_over(self):
        win, winner = self.winner()
        if win:
            print('Game over, player ' + str(winner) + ' wins')
            return True, winner
        elif not len(self.available_moves):
            print('Game over, tie')
            return True, -1
        else:
            return False, -1
        
        
class game(object):
    def __init__(self, board, **kwargs):
        self.board = board
        
    def graphic(self, board, player1, player2):
        pass
    
    def start_play(self, player1, player2, start_player = 0, is_shown = 1):
        # two human player
        self.board.init_board(start_player)
        p1, p2 = self.board.players
        player1.set_player_ind(p1)
        player2.set_player_ind(p2)
        players = {p1: player1, p2:player2}
        if is_shown:
            self.graphic(self.board, player1.player, player2.player)
        
        while(1):
            current_player = self.board.current_player()
            player_in_turn = players[current_player]
            move = player_in_turn.get_action(self.board)
            self.board.do_move(move)
            if is_shown:
                self.graphic(self.board, player1.player, player2.player)
            end, winner = self.board.game_end()
            if end:
                return winner   
            
        def start_self_play(self, player, is_shown = 1):
            pass
