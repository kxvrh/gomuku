#include "TreeNode.h"

TreeNode* TreeNode::add_child_with_action(Action& new_action)
{
	TreeNode* child = new TreeNode(_state, this);
	child->_action = _action;
	_children.push_back(child);
	child->_state = _state.apply_action(new_action);
	return child;
}

TreeNode * TreeNode::get_most_visited_child()
{
	int most_visited = -1;
	TreeNode* most_visited_child = NULL;
	for (int i = 0; i < _children.size(); i++)
	{
		TreeNode* node = this->get_child(i);
		if (node->get_visited() > most_visited)
		{
			most_visited = node->get_visited;
			most_visited_child = node;
		}
	}
	return most_visited_child;
}

TreeNode * TreeNode::select(double uct_k)
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
		double uct_score = uct_exploitation + uct_k * uct_exploration;
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
		_actions = _state.get_actions();
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

void TreeNode::update(double reward)
{
	_visits++;
	_value += reward;
}

bool TreeNode::is_terminal() const
{
	if (_state.has_a_winner() != -1)
		return true;
	else
		return false;
}

bool TreeNode::is_fully_expanded() const
{
	return _children.empty() == false && _children.size() == _actions.size();
}


