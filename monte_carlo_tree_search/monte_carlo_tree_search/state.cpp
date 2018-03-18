#include "State.h"

State& State::apply_action(Action& new_action)
{
	int ind = new_action.get_ind();
	if (available[ind] == 1)
	{
		occupied.push_back(ind);
		available[ind] = 0;
		board[ind] = player_id;
	}
	take_turn();
	return *this;
}

void State::take_turn()
{
	if (player_id == 1)
		player_id = 2;
	else
		player_id = 1;
}

void State::print_state()
{
	for (int i = 0; i < GRID; i++)
	{
		std::cout << " ";
		if (board[i] == 0)
			std::cout << "-";
		else if (board[i] == 1)
			std::cout << "o";
		else
			std::cout << 'x';
		if ((i + 1) % SIZE == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
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
		reward = 1000;
	else if (has_a_winner() == -1)
		reward = 1;
	//else
	//	reward = -100;
	return reward;
}

inline int State::has_a_winner() const
{
	int winner;
	for (int i = 0; i < occupied.size(); i++)
	{
		int ind = occupied[i];
		int player = board[ind];
		int x = ind / SIZE;
		int y = ind % SIZE;
		if (x + 5 < SIZE)
		{
			int j = 0;
			while (j < 5)
			{
				if (board[ind + j] != player)
					break;
				if (j == 4)
					return player;
				j++;
			}
		}
		if (y + 5 < SIZE)
		{
			int j = 0;
			while (j < 5)
			{
				if (board[ind + j*SIZE] != player)
					break;
				if (j == 4)
					return player;
				j++;
			}
		}
		if (x + 5 < SIZE && y + 5 < SIZE)
		{
			int j = 0;
			while (j < 5)
			{
				if (board[ind + j*(SIZE + 1)] != player)
					break;
				if (j == 4)
					return player;
				j++;
			}
		}
		if (x - 5 >= 0 && y + 5 < SIZE)
		{
			int j = 0;
			while (j < 5)
			{
				if (board[ind + j*(SIZE - 1)] != player)
					break;
				if (j == 4)
					return player;
				j++;
			}
		}
	}
	return -1;
}

State::State()
{
	for (int i = 0; i < GRID; i++)
	{
		available[i] = 1;
		board[i] = 0;
	}
	player_id = 1;
}

State::State(int p)
{
	for (int i = 0; i < GRID; i++)
	{
		available[i] = 1;
		board[i] = 0;
	}
	if (p == 1 || p == 2)
		player_id = p;
	else
		std::cout << ("mistake!");
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
	return *this;
}

State::State(const State & other)
{
	*this = other;
}

void State::get_actions(vector<Action>&actions)
{
	actions.clear();
	if (occupied.empty())
	{
		actions.push_back(Action(112, player_id));
		return;
	}
	for (int i = 0; i < GRID; i++)
	{
		if (available[i] == 1)
		{
			actions.push_back(Action(i, player_id));	
		}
	}
}

void State::get_adjcent_actions(vector<Action>& adjcent_actions)
{
	adjcent_actions.clear();
	if (occupied.empty())
	{
		adjcent_actions.push_back(Action(112, player_id));
		return;
	}
	for (int i = 0; i < occupied.size(); i++)
	{
		int ind = occupied[i];
		int ind_x = ind / SIZE;
		int ind_y = ind % SIZE;
		if (ind_x < SIZE - 1 && available[ind + 1] == 1)
			adjcent_actions.push_back(Action(ind + 1, player_id));//右
		if (ind_x > 0 && available[ind - 1] == 1)
			adjcent_actions.push_back(Action(ind - 1, player_id));//左
		if (ind_y > 0 && available[ind - SIZE] == 1)
			adjcent_actions.push_back(Action(ind - SIZE, player_id));//下
		if (ind_y < SIZE - 1 && available[ind + SIZE] == 1)
			adjcent_actions.push_back(Action(ind + SIZE, player_id));//上
		if (ind_x < SIZE - 1 && ind_y < SIZE - 1 && available[ind + 1 + SIZE] == 1)
			adjcent_actions.push_back(Action(ind + 1 + SIZE, player_id));//右上
		if (ind_x < SIZE - 1 && ind_y > 0 && available[ind + 1 - SIZE] == 1)
			adjcent_actions.push_back(Action(ind + 1 - SIZE, player_id));//右下
		if (ind_x > 0 && ind_y < SIZE - 1 && available[ind - 1 + SIZE] == 1)
			adjcent_actions.push_back(Action(ind - 1 + SIZE, player_id));//左上
		if (ind_x > 0 && ind_y > 0 && available[ind - 1 - SIZE] == 1)
			adjcent_actions.push_back(Action(ind - 1 - SIZE, player_id));//左下
		
	}
}

bool State::get_random_action(Action & action)
{
	vector<Action>actions;
	get_actions(actions);
	if (actions.empty())
		return false;
	else
	{
		int i = rand() % actions.size();
		action = actions[i];
		return true;
	}
}
