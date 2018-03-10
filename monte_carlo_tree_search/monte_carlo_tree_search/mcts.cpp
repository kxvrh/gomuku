#include "mcts.h"

Action MCTS::run(State & state)
{
	TreeNode root_node = TreeNode(state);
	TreeNode* best_node = NULL;
	for (int i = 0; i < max_iter; i++)
	{
		TreeNode* node = &root_node;
		State state = root_node.get_state();
		//1. SELECTION
		while (!node->is_terminal() && node->is_fully_expanded())
		{
			//non-terminal and fully expanded
			node = node->select();
		}
		//2. EXPANSION
		if (!node->is_terminal() && !node->is_fully_expanded())
			//non-terminal and not fully expanded
			node = node->expand();
		state = node->get_state();
		//3. SIMULATION
		if (!node->is_terminal())
		{
			Action action;
			for (int j = 0; j < sim_depth; j++)
			{
				if (state.get_random_action(action))
					state.apply_action(action);
				else
					break;
			}
		}
		//4. BACK-PROPAGATION
		while (node != NULL)
		{
			double reward = state.get_reward(node->get_player());
			node->update(reward);
			node = node->get_parent();
		}
		best_node = root_node.get_most_visited_child();
	}
	if (best_node)
		return best_node->get_action();
}
