#implement for pure monte carlo tree search
import tensorflow as tf
import numpy as np

class TreeNode(object):
    def _init_(self, parent, prior_p):
        self.parent = parent
        self.children = {}
        self.Q = 0 # its own value
        self.p = prior_p # prior probability
    
    
class MCTS(object):
    def _init_(self, board, **kwargs):
        self.board = board
        self.
    
    def slect(self):
        #start from root R and select successive child nodes down to a leaf node L
        
    
    def expand(self):
        # unless L ends the game with a win/loss for either player
        #create one (or more) child nodes and choose node C from one of them
        
    
    def simulate(self):
        #play a random playout from node C
        
    
    def pack_propagate(self):
        #use the result of the playout to update information in the nodes on the path from C to R

