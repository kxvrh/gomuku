#pragma once
#include "Action.h"
#include <vector>
#include <iostream>
using std::vector;

/*
actions in 15x15 board
0    1  ...  13 14
15  16  ...  28 29
30  31  ...  43 44
.   .       .   .
.   .       .   .

210 211 ... 223 224
*/

#define SIZE 15
#define GRID 225

class State
{
public:
	State();
	State(int p);
	State& operator = (const State& other);
	State(const State& other);

	//get all possible actions
	void get_actions(vector<Action>&actions);
	//more possible actions in current state(adjcent)
	void get_adjcent_actions(vector<Action>&adjcent_actions);
	//return false if no possible action found
	bool get_random_action(Action& action);
	State& apply_action(Action& new_action);

	//player who just made the action
	int get_player_id() { return player_id; }

	//player taking turn to play
	void take_turn();

	void print_state();

	bool is_over()const;
	//return 1 if player wins, 0 if player loses, 0.5 if draw
	double get_reward(int player)const;
	//return player's id if player wins, -1 if no winner
	int has_a_winner()const;
private:
	//1 for player1, 2 for player2
	int player_id;
	//all occupied actions
	vector<int>occupied;
	//available actions, 0 for unavailable, 1 for available
	int available[GRID];
	//15x15 board
	int board[GRID];
};

