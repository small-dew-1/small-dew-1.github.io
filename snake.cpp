#include<iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include<string>
#include <stdio.h>
#include <conio.h>

using std::cout;
using std::endl;
using std::string;

struct snake
{
	int pointx;
	int pointy;
	snake* nextpoint; //指向下一个身体节点的指针
};//定义蛇的身体节点（单向链表式定义） 

struct Food
{
	int x;
	int y;
}; //定义食物的坐标

const int height = 30;
const int width = 30;    //地图的高度宽度

int xspeed;
int yspeed;//蛇移动的方向和速度，默认向上

int maxscore = 0;
int nowscore = 0;//历史最高分数和当前最高分数

snake* tosnakehead;//指向蛇头的位置，全局变量，函数都要用
Food food = { 0,0 };//食物全局变量，被吃掉就重新生成

void gotoPos(int x, int y); //移动光标函数，移动到当前蛇头的位置
void printmenu(); //开始时打印主菜单
void initial(); //初始化游戏（生成游戏地图，蛇头，食物及其位置)
void printmap(); //生成游戏地图
void printsnake(); //打印出初始蛇的位置（后续只需要修改头尾即可）
void printfood(); //随机生成食物
void addhead(int x, int y); //添加蛇头，把旧蛇头变成蛇身
void deletetail(); //删除蛇尾
bool eatfood(); //判断是否吃掉食物
void move(); //重点函数，用于蛇的移动相关操作（更改方向，更新蛇位置，判断是否吃掉食物
bool hitwall(); //判断是否撞墙和蛇身，游戏结束标志
void freelist(); //游戏结束时要清除所有开辟空间，防止内存泄漏
void gameover(); //进行游戏结束操作结算

int main()
{
;
	while (1)
	{
		system("cls");
		printmenu();

		string a;
		while (1)
		{
			std::cin >> a;
			if (a == "q") { return 0; }
			if (a == "e")
			{
				break;
			}
			else {
				cout << "输入错误，请重新输入：";
			}
		} //开始游戏

		tosnakehead = new snake{ 0,0, nullptr};
		system("cls");
		initial(); //首先初始化
		Sleep(5000);
		while (1)
		{
			move();

			if (hitwall())
			{
				gameover();
				Sleep(1000);
				break;
			}

			Sleep(300);
		}

		delete tosnakehead; //一次游戏结束删除内存
	}

	gotoPos(0, height + 2);
	return 0;
}

void gotoPos(int x, int y) {
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor); //设置光标位置
}//移动光标函数，移动到当前蛇头的位置

void printmenu()
{
	cout << "欢迎来到贪吃蛇小游戏" << endl;
	cout << "历史最高分：" << maxscore << endl;
	cout << "输入e开始游戏，输入q退出游戏" << endl;

} //开始时打印主菜单

void printmap()
{
	int i, j;
	for (i = 0; i <=2*(width + 1); i+=2)
	{
		gotoPos(i, 0);
		cout << "■";

		gotoPos(i, height + 1);
		cout << "■";
	}

	for (i = 0; i <= height+1; i++)
	{
		gotoPos(0,i);
		cout << "■";
		
		gotoPos(2*(width+1), i);
		cout << "■";
	}

	for(i=2;i<=2*width;i+=2)
	{
		for(j=1;j<=height;j++)
		{
			gotoPos(i, j);
			cout << "□";
		}
	}
}// 生成游戏地图

void printsnake()
{
	snake* snakehead = new snake{ 20,11,nullptr }; //生成蛇头 
	tosnakehead->nextpoint = snakehead; //全局变量指向蛇头 
	gotoPos(snakehead->pointx, snakehead->pointy);
	cout << "●";
} //打印出初始蛇的位置（后续只需要修改头尾即可）

void printfood()
{
	while (1)
	{
		srand(unsigned(time(NULL)));
		food.x = 2*(1 + rand() % (width));
		food.y = 1 + rand() % (height);
		int t = 0;
		snake* p = tosnakehead;
		while (p->nextpoint != nullptr)
		{
			p = p->nextpoint;
			if ((food.x == p->pointx) && (food.y == p->pointy))
			{
				t = 1;
				break;
			}//判断是否与蛇重合，重合重新生成
		}

		if (t == 0)
		{
			gotoPos(food.x, food.y);
			cout << "★";
			break;
		}
	}
} //随机生成食物

void initial()
{
	xspeed = 0;
	yspeed = -1;
	nowscore = 0;
	printmap();
	printsnake();
	printfood();
}//初始化游戏（生成游戏地图，蛇头，食物及其位置)

void addhead(int x, int y)
{
	snake* newhead = new snake{ x,y,tosnakehead->nextpoint }; //生成新蛇头
	gotoPos(tosnakehead->nextpoint->pointx, tosnakehead->nextpoint->pointy);
	cout << "■";//更改旧蛇头
	tosnakehead->nextpoint = newhead;
	gotoPos(tosnakehead->nextpoint->pointx, tosnakehead->nextpoint->pointy);
	cout << "●";//添加新蛇头
} //添加蛇头，把旧蛇头变成蛇身

void deletetail()
{
	snake* p = tosnakehead;
	while (p->nextpoint->nextpoint != nullptr) {
		p = p->nextpoint;
	}//定位到蛇尾前一个
	snake* p1 = p;
	p1 = p1->nextpoint; //定位到蛇尾
	p->nextpoint = nullptr;  //更新新蛇尾
	gotoPos(p1->pointx, p1->pointy);
	cout << "□";

	delete p1;  //删除蛇尾
} //删除蛇尾 

bool eatfood()
{
	if (tosnakehead->nextpoint->pointx == food.x && tosnakehead->nextpoint->pointy == food.y)
	{
		return true;
	}
	else {
		return false;
	}
} //判断是否吃掉食物

void move()
{
	//改变方向
	char cinput;
	if (_kbhit())
	{
		cinput = _getch();

		switch (cinput)
		{
		case 87: case 119:
		{
			if (xspeed == 0 && yspeed == 1) {
				break;
			}
			else {
				xspeed = 0;
				yspeed = -1;
				break;
			}
		}

		case 53: case 115:
		{
			if (xspeed == 0 && yspeed == -1) {
				break;
			}
			else {
				xspeed = 0;
				yspeed = 1;
				break;
			}
		}

		case 65: case 97:
		{
			if (xspeed == 2 && yspeed == 0) {
				break;
			}
			else {
				xspeed = -2;
				yspeed = 0;
				break;
			}
		}

		case 68: case 100:
		{
			if (xspeed == -2 && yspeed == 0) {
				break;
			}
			else {
				xspeed = 2;
				yspeed = 0;
				break;
			}
		}
		}//注意：蛇头不能掉头，只能转向！
	}

	//更新蛇头
	addhead(tosnakehead->nextpoint->pointx + xspeed, tosnakehead->nextpoint->pointy + yspeed);

	//判断是否要删除蛇尾并执行
	if (eatfood())
	{
		nowscore++; //加分
		printfood();
	}
	else {
		deletetail();
	}

} //重点函数，用于蛇的移动相关操作（更改方向，更新蛇位置，判断是否吃掉食物

bool hitwall()
{
	if (tosnakehead->nextpoint->pointx == 0 || tosnakehead->nextpoint->pointx == 2*(width + 1) ||
		tosnakehead->nextpoint->pointy == 0 || tosnakehead->nextpoint->pointy == height + 1) {
		return true;
	} //是否与墙相碰

	snake* p = tosnakehead->nextpoint;
	while (p->nextpoint != nullptr)
	{
		p = p->nextpoint;
		if (p->pointx == tosnakehead->nextpoint->pointx && p->pointy == tosnakehead->nextpoint->pointy)
		{
			return true;
		}
	} //是否与蛇身相碰

	return false;
} //判断是否撞墙和蛇身，游戏结束标志

void freelist()
{
	snake* p = tosnakehead->nextpoint;
	while (p->nextpoint != nullptr)
	{
		snake* p1 = p;
		p = p->nextpoint;
		delete p1;
	}
	delete p;
} //游戏结束时要清除所有开辟空间，防止内存泄漏

void gameover()
{
	system("cls");
	cout << "Game Over" << endl;
	cout << "Your Score: " << nowscore << endl;

	if (maxscore < nowscore) maxscore = nowscore;

	freelist();
} //进行游戏结束操作结算
