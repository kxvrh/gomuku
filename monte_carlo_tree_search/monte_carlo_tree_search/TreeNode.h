#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "Action.h"
#include "State.h"
using namespace std;
#define EPSILON 0.000001

class TreeNode
{
public:
	TreeNode(const State& state, Action& action, TreeNode* parent = NULL)
		:_state(state), _action(action),_parent(parent),_value(0),_visits(0){}
	~TreeNode(){}

	const State& get_state() const { return _state; }
	const Action& get_action() const { return _action; }
	TreeNode* get_parent() { return _parent; }
	TreeNode* get_child(int i) { return _children[i]; }
	int children_num()const { return _children.size(); }
	double get_value()const { return _value; }
	int get_visited()const { return _visits; }

	TreeNode* select();
	TreeNode* expand();
	void simulate();
	void update(vector<double>reward);
	
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
	int player_id;
	int depth;

	TreeNode* add_child_with_action(Action& new_action);
};

