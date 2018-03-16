#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "mcts.h"
#include "jsoncpp\json.h"
using namespace std;

/*
void placeAt(int x, int y)
{
if (x >= 0 && y >= 0) {
Grid[x][y] = true;
}
}*/

/*
int main()
{
// 读入JSON
string str;
getline(cin, str);
Json::Reader reader;
Json::Value input;
reader.parse(str, input);

// 分析自己收到的输入和自己过往的输出，并恢复状态
string data = input["data"].asString(); // 该对局中，以前该Bot运行时存储的信息
int turnID = input["responses"].size();
for (int i = 0; i < turnID; i++)
{
istringstream in(input["requests"][i].asString()),
out(input["responses"][i].asString());

// 根据这些输入输出逐渐恢复状态到当前回合
}

// 看看自己本回合输入
istringstream in(input["requests"][turnID].asString());

// 做出决策存为myAction

// 输出决策JSON
Json::Value ret;
//ret["response"] = myAction;
//ret["data"] = myData; // 可以存储一些前述的信息，在整个对局中使用
Json::FastWriter writer;
cout << writer.write(ret) << endl;
return 0;
}
*/
//#define FLAG

int main()
{
	State state;
	state.print_state();
	while (!state.is_over())
	{
		int player = state.get_player_id();
		if (player == 1)//computer 1
		{
			MCTS mcts;
			Action action;
			action = mcts.run(state);
			state.apply_action(action);
			std::cout << "Computer1 chose action " << action.get_x() << " " << action.get_y() << endl;
			//cout << "Computer1 chose action " << action.get_ind() << endl;
		}
#ifndef FLAG
		if (player == 2)//computer 2
		{
			MCTS mcts;
			Action action;
			action = mcts.run(state);
			state.apply_action(action);
			std::cout << "Computer2 chose action " << action.get_x() << " " << action.get_y() << endl;
			//cout << "Computer2 chose action " << action.get_ind() << endl;
		}
#endif 

#ifdef FLAG
		else//human player
		{
			std::cout << "please input your action:";
			int a, b;
			cin >> a >> b;
			int m = (a - 1)*SIZE + b - 1;
			Action action(m, 2);
			state.apply_action(action);
		}
#endif 
		
		state.print_state();
	}
	int winner = state.has_a_winner();
	if (winner == 1)
		cout << "player 1 wins!\n";
	else if (winner == 2)
		cout << "player 2 wins!\n";
	else
		cout << "draw! nobody wins!\n";
}
