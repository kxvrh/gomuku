#include "TreeNode.h"

TreeNode* TreeNode::add_child_with_action(Action& new_action)
{
	TreeNode* child = new TreeNode(_state, new_action, this);
	_children.push_back(child);
	child->_state = _state.apply_action(new_action);
	return child;
}

TreeNode * TreeNode::select()
{
	if (_children.empty())
		return NULL;

	double best_score = 0;
	TreeNode* best_child = NULL;
	for (int i = 0; i < _children.size(); i++)
	{
		TreeNode* child = _children[i];
		double uct_exploitation = _value / _visits + EPSILON;
		double uct_exploration = sqrt(log(_visits) / child->get_visited() + EPSILON);
		double uct_score = uct_exploitation + uct_exploration;
		if (uct_score > best_score)
		{
			best_score = uct_score;
			best_child = child;
		}
	}
	return best_child;
}

TreeNode* TreeNode::expand()
{
	if (_actions.empty())
	{
		_state.get_actions(_actions);
	}
	srand(time(0));
	int random = rand() % _actions.size();
	TreeNode* expanded_node = this->add_child_with_action(_actions[random]);
	return expanded_node;
}

void TreeNode::simulate()
{
	while (!_actions.empty())
	{
		int random = rand() % _actions.size();
		Action random_action = _actions[random];
		_state.apply_action(random_action);
	}
}

void TreeNode::update(vector<double>reward)
{
	_visits++;
	_value += reward[_state.get_player_id()];
}


