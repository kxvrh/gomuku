#include "State.h"

State& State::apply_action(Action& new_action)
{
	int ind = new_action.get_ind();
	if (available[ind] == 1)
	{
		occupied[ind] = 1;
		available[ind] = 0;
	}
	return *this;
}

bool State::is_over() const
{
	if (occupied.size() == GRID)
		return true;
	if (has_a_winner() != -1)
		return true;
	return false;
}

double State::get_reward(int player) const
{
	double reward = 0;
	if (has_a_winner() == player)
		reward = 1;
	else if (occupied.size() == GRID)
		reward = 0.5;
	return reward;
}

inline int State::has_a_winner() const
{
	int winner;
	for (int i = 0; i < occupied.size(); i++)
	{
		int ind = occupied[i];
		int player = board[ind];
		if (ind + 5 < SIZE)
		{
			int j = 0;
			while (j < 5)
			{
				if (board[ind + j] != player)
					break;
				if (j = 4)
					return player;
			}
		}
		if (ind + 5 * SIZE < GRID)
		{
			int j = 0;
			while (j < 5)
			{
				if (board[ind + j*SIZE] != player)
					break;
				if (j = 4)
					return player;
			}
		}
		if (ind + 5 * (SIZE + 1) < SIZE)
		{
			int j = 0;
			while (j < 5)
			{
				if (board[ind + j*(SIZE + 1)] != player)
					break;
				if (j = 4)
					return player;
			}
		}
		if (ind - 5 * (SIZE - 1) > 0)
		{
			int j = 0;
			while (j < 5)
			{
				if (board[ind - j*(SIZE - 1)] != player)
					break;
				if (j = 4)
					return player;
			}
		}
		return -1;
	}
}

State::State()
{
	for (int i = 0; i < GRID; i++)
	{
		available[i] = 0;
		board[i] = 0;
	}
}

State & State::operator=(const State & other)
{
	// TODO: insert return statement here
	for (int i = 0; i < GRID; i++)
	{
		available[i] = other.available[i];
		board[i] = other.board[i];
	}
	occupied = other.occupied;
	player_id = other.player_id;
}

State::State(const State & other)
{
	*this = other;
}

vector<Action>& State::get_actions()
{
	vector<Action> actions;
	for (int i = 0; i < GRID; i++)
	{
		if (available[i] == 1)
		{
			actions.push_back(Action(i, player_id));
			available[i] = 0;
			occupied[i] = player_id;
			
		}
	}
	return actions;
}

bool State::get_random_action(Action & action)
{
	vector<Action>actions = get_actions();
	if (actions.empty())
		return false;
	else
	{
		int i = rand() % actions.size();
		action = actions[i];
		return true;
	}
}
