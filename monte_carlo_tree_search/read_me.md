 # c++ implement of gomuku using monte carlo tree search
# （一）蒙特卡洛树搜索算法：
1. TreeNode类：实现蒙特卡洛树结点

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
//1 for player1, 2 for player2
int _player_id;//当前玩家

2. MCTS类：实现蒙特卡洛树搜索算法

MCTS();//构造函数

Action run(State& state);//根据当前状态执行蒙特卡洛树搜索，返回最优动作

double uct_k;//参数

int max_iter;//最大迭代次数

int sim_depth;//simulation部分模拟深度


# （二）五子棋部分
1. State类

State();//构造函数，当前玩家缺省值1

State(int p);//构造函数，当前玩家p

State& operator = (const State& other);//重载运算符=

State(const State& other);

//get all possible actions
void get_actions(vector<Action>&actions);//返回当前状态所有可能动作
 
//return false if no possible action found
bool get_random_action(Action& action);//返回任意当前可能动作，如果没有可执行动作，返回false
 
State& apply_action(Action& new_action);//执行动作
 
//player who just made the action
int get_player_id() { return player_id; }
 
//player taking turn to play
void take_turn();

void print_state();//打印当前棋盘状态
 
bool is_over()const;
//return 1 if player wins, 0 if player loses, 0.5 if draw
 
double get_reward(int player)const;//返回权值
//return player's id if player wins, -1 if no winner
int has_a_winner()const;
//1 for player1, 2 for player2
int player_id;
//all occupied actions
vector<int>occupied;//棋盘中已被占据的位置
//available actions, 0 for unavailable, 1 for available
int available[GRID];//棋盘中空余位置
//15x15 board
int board[GRID];//棋盘
