#pragma once
#include "Action.h"
#include <vector>
using std::vector;
/*
actions in 19x19 board
342 343 ... 359 360
.   .       .   .
.   .       .   .
38  39  ...  55 56
19  20  ...  36 37
0    1  ...  17 18
*/

#define SIZE 15
#define GRID 225

class State
{
public:
	void get_actions(vector<Action>& actions)//get all possible actions
	{
		for (int i = 0; i < GRID; i++)
		{
			if (board[i] == 0)
				actions.push_back(Action(i, player_id));
		}
	}
	State& apply_action(Action& new_action);
	int get_player_id() { return player_id; }
	int has_a_winner()const;
private:
	//1 for player1, 2 for player2
	int player_id;
	//15x15 board
	int board[GRID];
};

