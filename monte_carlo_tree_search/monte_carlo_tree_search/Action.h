#pragma once

#define SIZE 5

class Action
{
public:
	Action() {};
	Action(int ind, int player):_ind(ind), _player(player){};
	~Action() {};
	int get_x()const { return _ind / SIZE; }
	int get_y()const { return _ind % SIZE; }
	int get_ind()const { return _ind; }
private:
	int _ind;
	int _player;
};
