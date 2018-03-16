#pragma once

#define SIZE 15

class Action
{
public:
	Action() {};
	Action(int ind, int player);
	~Action() {};
	int get_x()const { return _ind / SIZE + 1; }
	int get_y()const { return _ind % SIZE + 1; }
	int get_ind()const { return _ind; }
private:
	int _ind;
	int _player;
};
