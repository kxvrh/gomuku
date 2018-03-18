#include "mcts.h"

MCTS::MCTS()
{
	max_iter = 2000;
	sim_depth = 15;
	uct_k = log(2);
}

Action MCTS::run(State & state)
{
	TreeNode root_node = TreeNode(state);
	TreeNode* best_node = NULL;
	for (int i = 0; i < max_iter; i++)
	{
		TreeNode* node = &root_node;
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
		State state(node->get_state());
		//3. SIMULATION
		if (!node->is_terminal())
		{
			for(int i = 0;i<sim_depth;i++)
			{
				vector<Action>actions;
				state.get_adjcent_actions(actions);
				Action action;
				if (state.get_random_action(action))
				{
					state.apply_action(action);
					state.get_adjcent_actions(actions);
				}
				else
					break;
			}
		}
		//4. BACK-PROPAGATION
		while (node != NULL)
		{
			int player = node->get_player();
			double reward = state.get_reward(player);
			node->update(reward);
			node = node->get_parent();
		}
		best_node = root_node.get_most_visited_child();
	}
	if (best_node)
	{
		Action chosen;
		 chosen = best_node->get_action();
		 return chosen;
	}
		
}
