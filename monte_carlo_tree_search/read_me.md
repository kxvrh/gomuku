# (一）系统关键技术
1.3.1 Minimax算法

Minimax是一种找出失败的最大可能性中的最小值的算法，一方要在可选的选项中选择将其优势最大化的选择，另一方则选择令对手优势最小化的方法。

Maximin是该玩家在不知道其他玩家的动作的情况下能够确定的最高分数，也就是，当其他玩家知道了该玩家的动作的情况下能让该玩家得到的最低分数，即
 
其中，i为该玩家，-i为其他玩家，ai为该玩家做出的动作，a-i为其他玩家做出的动作，vi是该玩家的值函数。

Minimax是该玩家在知道其他玩家的动作的情况下能够确定的最高分数，也就是，当其他玩家不知道该玩家的动作的情况下能让该玩家得到的最低分数，即
 
简而言之，Minimax算法假设对手每一步都会将我方引入从当前看理论上价值最小的格局方向，即对手具有完美决策能力。因此我方的策略应该是选择那些对方所能达到的让我方最差情况中最好的，也就是让对方在完美决策下所对我造成的损失最小。然而当minimax应用于五子棋时，搜索树将会变得太广太深而不切实际，这时我们引进蒙特卡洛树搜索来解决这些问题。

1.3.2蒙特卡洛树搜索算法
蒙特卡洛树搜索（Monte Carlo Tree Search）是一种用于某些决策过程的启发式搜索算法，每个循环中包含以下步骤2:
1. 选择（Selection）：从根结点R开始，选择连续的子结点向下至叶子结点L。后面给出了一种选择子结点的方法，让游戏树向最优的方向扩展，这是蒙特卡洛树搜索的精要所在。
2. 扩展（Expansion）：除非任意一方的输赢使得游戏在L结束，否则创建一个或多个子结点并选取其中一个结点C。
3. 仿真（Simulation）：在从结点C开始，用随机策略进行游戏，又称为playout或者rollout。
4. 反向传播（Backpropagation）：使用随机游戏的结果，更新从C到R的路径上的结点信息。
 
我们采用上限置信区间算法3（Upper Confidence Bound 1 applied to trees）来计算并选择最优子结点，其具体公式为
 
其中 x 是节点的当前胜率估计，N 是节点的访问次数。该公式平衡了探索与利用（exploration and exploitation）,第一项变量代表了利用，即对已知条件的利用，第二项代表了探索，即对未知条件的探索。 该考虑来源于经典的Multi-armed bandit问题，即通过决定使用哪台老虎机、每个老虎机使用多少次、用怎样顺序使用、是否继续使用该台老虎机还是尝试下一台老虎机，来达到收益最大化的问题。

1.3.3五子棋局面估值
方案一：我们采用较为简单的方式对当前局面进行估值，用0~1表示AI胜利的概率，即
        x = 1    若当前局面中AI胜利
        x = 0    若当前局面中AI失败
        x = 0.5  若当前局面中暂无胜方

方案二：我们用不同数量级的权值表示当前局面，以使AI能够更好的辨别更好的动作，即
        x = 100  若当前局面中AI胜利
        x = 0    若当前局面中AI失败
        x = 1    若当前局面中暂无胜方

以上方案可以粗略地表示对当前局面的估值，但因为未对五子棋具体局面，如冲四、活三等局面进行更详细的评估，AI仍表现出一定的随机性，例如已连成活三时不会锁定冲四/活四，这一点是我们在后续优化中要重点改进的部分。

（二）算法设计
2.1系统整体思路
该程序分两部分实现，五子棋的底层框架及游戏AI，根据游戏规则设计五子棋底层框架，运用蒙特卡洛树搜索算法实现博弈AI，根据具体情形设计端口进行对接。

2.2关键数据结构设计
五子棋部分包含State以及Action类，State表示当前棋盘，包括判断局势、获取可能动作等，Action表示玩家做出的动作。
AI部分包含TreeNode以及mcts类，TreeNode表示蒙特卡洛树搜索中每一个结点，包括该结点所表示的State等信息，以及蒙特卡洛树搜索中选择、扩展、更新部分，mcts中实现蒙特卡洛树搜索具体算法。

2.3五子棋功能相关设计
Action类：包含一个int类的值_ind，并可以返回ind值所对应矩阵中的x，y值，包含一个int值_player,储存棋子颜色（选手1/2）。
State类：
函数部分:
//获取棋盘上所有可以落子的位置
	void get_actions(vector<Action>&actions);
	//获取棋盘上所有棋子的周围八个方向可落子位置的集合
	void get_adjcent_actions(vector<Action>&adjcent_actions);
	//从当前可落子位置的集合中随机选取一个落子位置
	bool get_random_action(Action& action);
	//落子，并转换玩家
	State& apply_action(Action& new_action)	
int get_player_id() { return player_id; };//获得当前状态即将执行落子的玩家
void take_turn();//玩家转换
void print_state();//打印棋盘
	//判断游戏是否结束（平局或某一玩家获胜）
	bool is_over()const;
	//返回当前局面分数，胜利为1，失败为0，平局为0.5
	double get_reward(int player)const;
	//返回获胜玩家id，若无玩家获胜则为-1
	int has_a_winner()const;
变量部分:
//1是一号玩家，2是2号玩家
	int player_id;
	//已落子的位置集合
	vector<int>occupied;
	//记录当前棋盘落子状态，0为不可落子（已落子），1为可落子（该位置为空）
	int available[GRID];
	//15*15的棋盘，int值为玩家该点落子的玩家id，0为空（未落子）
	int board[GRID];

2.4 AI功能相关设计
//
TreeNode类：
函数部分：
TreeNode(State& state, TreeNode* parent = NULL)//构造函数，初始化变量
	~TreeNode(){}//析构函数

	const State& get_state() const { return _state; }//返回当前棋盘状态
	const Action& get_action() const;//返回得到当前结点的动作
	TreeNode* get_parent() { return _parent; }//返回当前结点的父结点
	TreeNode* get_child(int i) { return _children[i]; }//返回当前结点的第i个子结点
	int children_num()const { return _children.size(); }//返回当前结点子结点个数
	double get_value()const { return _value; }//返回当前结点权值
	int get_visited_num()const { return _visits; }//返回当前结点被访问次数
	int get_player()const { return _player_id; }//返回当前棋盘出手的玩家

	TreeNode* add_child_with_action(Action& new_action);//延伸部分，增加一个子结点
	TreeNode* get_most_visited_child();//返回被访问次数最多的子结点

	TreeNode* select(double uct_k = sqrt(2));//蒙特卡洛树搜索选择部分
	TreeNode* expand();//蒙特卡洛树搜索延伸部分
	void update(double reward);//向上更新权值

	bool is_terminal()const;//判断当前结点游戏是否结束
	bool is_fully_expanded()const;//判断当前结点所有子结点是否都expand并simulate
变量部分：
//state of this node
	State _state;//该结点状态
	//action that led to current state
	Action _action;//得到当前结点的动作
	//all possible actions in current state
	vector<Action>_actions;//当前状态所有可能的动作
	//parent of this node
	TreeNode* _parent;//当前结点的父结点
	//all current children
	vector<TreeNode*> _children;//当前结点所有子结点
	//value of this node
	double _value;//当前结点权值
	//num of being visited
	int _visits;//当前结点被访问次数
	//current player, 1 for player1, 2 for player2
	int _player_id;//当前玩家
