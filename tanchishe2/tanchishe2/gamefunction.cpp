#include<iostream>
#include <windows.h>
#include<string>

#include "gamefunction.h"
#include "extern.h"

using std::cout;
using std::endl;
using std::string;

void printmenu()
{
	cout << "欢迎来到贪吃蛇小游戏" << endl;
	cout << "历史最高分：" << maxscore << endl;
	cout << "输入e开始游戏，输入q退出游戏" << endl;

} //开始时打印主菜单