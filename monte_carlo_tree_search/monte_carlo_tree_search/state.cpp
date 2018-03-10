#include "State.h"

State& State::apply_action(Action& new_action)
{
	int ind = new_action.get_ind();
	board[ind] = player_id;
	return *this;
}

inline int State::has_a_winner() const
{

}

