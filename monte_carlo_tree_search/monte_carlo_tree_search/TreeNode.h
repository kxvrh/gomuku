#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "Action.h"
#include "State.h"

#define EPSILON 0.000001

class TreeNode
{
public:
	TreeNode(State& state, TreeNode* parent = NULL)
		:_state(state), _action(),_parent(parent),_value(0),_visits(0), _player_id(state.get_player_id()){}
	~TreeNode(){}

	const State& get_state() const { return _state; }
	const Action& get_action() const;
	TreeNode* get_parent() { return _parent; }
	TreeNode* get_child(int i) { return _children[i]; }
	int children_num()const { return _children.size(); }
	double get_value()const { return _value; }
	int get_visited_num()const { return _visits; }
	int get_player()const { return _player_id; }

	TreeNode* add_child_with_action(Action& new_action);
	TreeNode* get_most_visited_child();

	TreeNode* select(double uct_k = sqrt(2));
	TreeNode* expand();
	void update(double reward);

	bool is_terminal()const;
	bool is_fully_expanded()const;
	
private:
	//state of this node
	State _state;
	//action that led to current state
	Action _action;
	//all possible actions in current state
	vector<Action>_actions;
	//parent of this node
	TreeNode* _parent;
	//all current children
	vector<TreeNode*> _children;
	//value of this node
	double _value;
	//num of being visited
	int _visits;
	//1 for player1, 2 for player2
	int _player_id;
};

