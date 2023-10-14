#include<iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include<string>
#include <stdio.h>
#include <conio.h>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct snake
{
	int pointx;
	int pointy;
	snake* nextpoint; //指向下一个身体节点的指针
	snake(int x=0,int y=0,snake* p=nullptr):pointx(x),pointy(y),nextpoint(p){}
};//定义蛇的身体节点（单向链表式定义） 

struct Food
{
	int x;
	int y;
}; //定义食物的坐标

int height = 28;
int width = 28;    //地图的高度宽度,默认为最大

int xspeed;
int yspeed;//蛇移动的方向和速度，默认向上

string maplarge="large";//用于记录开始的地图尺寸
int mapgrade=0;
int grade = 1;//用于记录等级

int maxscore[2][3]= {0,0,0,0,0,0};
int nowscore[2][3]= {0,0,0,0,0,0};//历史最高分数和当前最高分数

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
void pause();//用于实现游戏暂停
void back_to_menu();//用于返回菜单
void preserve();//保存游戏记录
void showmaxscore();//读入历史最高分
void changemap();//选择地图大小 
void printmaxscore();//显示最高分数 
void changegrade();//选择难度
void restart();//用于重新开始 
void screen();//用于固定窗口
void ptr();//用于隐藏光标
void noroller();//用于删除滚轮

int main()
{
	screen();
	ptr();
	noroller();
	while (1)
	{
		system("cls");
		showmaxscore();
		printmenu();   //打印菜单

		char a;
		while (1)
		{
			a = _getch();
			if (a == 'e' || a == 'E' )
				break;
			if (a == 'q' || a == 'Q')
				exit(0);
			if(a == 'g' || a == 'G')
			{
				printmaxscore();
				system("cls");
				printmenu();
			}
			if(a == 'n' || a == 'N')
			{
				changemap();
				system("cls");
				printmenu();
			}
			if(a == 'm' || a == 'M')
			{
				changegrade();
				system("cls");
				printmenu();
			}
				
		} //开始游戏
		
		tosnakehead = new snake(0,0, nullptr);
		system("cls");
		initial(); //首先初始化
		Sleep(3000); //程序挂起3秒，3秒后游戏会自动开始（可以改成暂停功能）
		
		while (1)
		{
			move();
			if (hitwall())
			{
				gameover();
				preserve();
				Sleep(1000); 
				break;
			}

			Sleep(300/grade);
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

void showmaxscore()
{
	std::ifstream show;
	show.open("maxscore[0,0].txt");
	show>>maxscore[0][0];
	show.close();
	
	show.open("maxscore[0,1].txt");
	show>>maxscore[0][1];
	show.close();
	
	show.open("maxscore[0,2].txt");
	show>>maxscore[0][2];
	show.close();
	
	show.open("maxscore[1,0].txt");
	show>>maxscore[1][0];
	show.close();
	
	show.open("maxscore[1,1].txt");
	show>>maxscore[1][1];
	show.close();
	
	show.open("maxscore[1,2].txt");
	show>>maxscore[1][2];
	show.close();
}//读入最高分 

void printmaxscore(){
	system("cls");
	cout << "难度1，地图大最高分" << maxscore[0][0] <<endl;
	cout << "难度1，地图中最高分" << maxscore[0][1] <<endl;
	cout << "难度1，地图小最高分" << maxscore[0][2] <<endl;
	cout << "难度2，地图大最高分" << maxscore[1][0]<<endl;
	cout << "难度2，地图中最高分" << maxscore[1][1]<<endl;
	cout << "难度2，地图小最高分" << maxscore[1][2]<<endl;
	cout << "输入Q退出" << endl;
	
	char a1;
	while (1)
	{
		a1 = _getch();
		if (a1 == 'q' || a1 == 'Q')
			break;
	}
}//显示最高分数 

void changegrade(){
	system("cls");
	cout << "请选择难度大小 ：" << endl << "输入1  难度1" << endl << "输入2  难度2" << endl;
	char ccin;
		while (1) 
		{
			ccin = _getch();
			if (ccin == '1'){
				grade=1;
				break;
			}
			if (ccin == '2'){
				grade=2;
				break;
			}	
		} 
}//选择难度

void printmenu()
{
	cout << "欢迎来到贪吃蛇小游戏" << endl;
	cout << "输入G查看历史最高分" << endl; 
	cout << "输入N选择地图大小，当前地图大小：" << maplarge << endl;
	cout << "输入M选择难度等级（速度大小），当前难度等级：" << grade << endl;
	cout << "输入E 开始游戏" <<endl<< "输入Q 结束游戏" << endl;

} //开始时打印主菜单

void changemap(){
	system("cls");
	cout << "请选择地图大小 ：" << endl << "输入L  生成大地图" << endl << "输入M  生成中地图" << endl <<"输入S  小地图"<<endl;
	char in;
		while (1) 
		{
			in = _getch();
			if (in == 'L' || in == 'l' || in == 'M' || in == 'm' || in == 'S' || in == 's')
				break;
		}
		switch (in)
		{
		case 76:case 108: {width = 28; height = 28; mapgrade = 0; maplarge = "large"; break; }
		case 77:case 109: {width = 20; height = 20; mapgrade=1; maplarge="middle"; break; }
		case 83:case 115: {width = 12; height = 12; mapgrade=2; maplarge="small"; break; }
		}
}//修改地图大小 

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
	
	gotoPos(2*width+15, height / 2-2);
	cout << "按下ESC 暂停游戏，按下任意键继续游戏";
	gotoPos(2*width+15,height/2+2);
	cout << "按下M 返回菜单";
	gotoPos(2 * width + 15, height / 2 + 6);
	cout << "按下R重新开始";
}// 生成游戏地图

void printsnake()
{
	snake* snakehead = new snake(width,height/2,nullptr); //生成蛇头 
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
	yspeed = 1;
	nowscore[grade-1][mapgrade] = 0;
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

		case 83: case 115:
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
		
		case 77: case 109:
		{
			back_to_menu();//输入M后返回菜单,就是退出游戏重新开始功能 
			break;
		}
		
		case 27:
		{
			pause(); //执行暂停操作
			break;
		}//注意：蛇头不能掉头，只能转向！
		
		case 82:case 114:
		{
			restart();
			break;
		}//用于重新开始
		
		}
		
		}
		
	//更新蛇头
	addhead(tosnakehead->nextpoint->pointx + xspeed, tosnakehead->nextpoint->pointy + yspeed);
	
	//判断是否要删除蛇尾并执行
	if (eatfood())
	{
		nowscore[grade-1][mapgrade]++; //加分
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
	cout << "Your Score: " << nowscore[grade-1][mapgrade] <<endl;

	if (maxscore[grade-1][mapgrade] < nowscore[grade-1][mapgrade]) maxscore[grade-1][mapgrade] = nowscore[grade-1][mapgrade];
	cout << "按任意键返回菜单选项";
	system("pause>nul");
	freelist();
} //进行游戏结束操作结算

void pause()
{
	system("pause>nul");
}

void back_to_menu()
{
	system("cls");
	freelist();
	delete tosnakehead; 
	main();      //用于返回菜单
}

void preserve()
{
	std::ofstream score;
	if(grade==1 && mapgrade==0){
		score.open("maxscore[0,0].txt");
		if(score.is_open())
		score<<maxscore[0][0];
		score.close();
	}
	if(grade==1 && mapgrade==1){
		score.open("maxscore[0,1].txt");
		if(score.is_open())
		score<<maxscore[0][1];
		score.close();
	}
	if(grade==1 && mapgrade==2){
		score.open("maxscore[0,2].txt");
		if(score.is_open())
		score<<maxscore[0][2];
		score.close();
	}
	if(grade==2 && mapgrade==0){
		score.open("maxscore[1,0].txt");
		if(score.is_open())
		score<<maxscore[1][0];
		score.close();
	}
	if(grade==2 && mapgrade==1){
		score.open("maxscore[1,1].txt");
		if(score.is_open())
		score<<maxscore[1][1];
		score.close();
	}
	if(grade==2 && mapgrade==2){
		score.open("maxscore[1,2].txt");
		if(score.is_open())
		score<<maxscore[1][2];
		score.close();
	}
}

void restart()
{
	system("cls");//先清屏
	freelist();
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info); 
	initial();
	Sleep(3000);
	while (1)
	{
		move();
		if (hitwall())
		{
			gameover();
			preserve();
			Sleep(1000);
			break;
		}

		Sleep(300/grade);
	}
	
	system("cls");
	delete tosnakehead; 
	main();      //用于返回菜单
}
void screen()    //用于固定贪吃蛇界面大小以及删除最大化最小化
{
	SetWindowLongPtrA(
		GetForegroundWindow(),
		GWL_STYLE,
		GetWindowLongPtrA(GetForegroundWindow(), GWL_STYLE)
		& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX           //删除最大化最小化以及大小控制
	);
}
void ptr()   //用于隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//创建一个光标结构体，前一个值为光标的size（int），后一个值为光标的可见性（bool）
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info); //将光标结构体应用到控制台光标上，从而隐藏光标
}
void noroller()            //用于删除滚轮
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	SMALL_RECT rect = csbiInfo.srWindow;     //取得窗口的左上角和左下角的坐标
	COORD size = { rect.Right + 1 ,rect.Bottom + 1 };	//取得右下角坐标+1的位置 
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);  //定义缓冲区大小，保持缓冲区大小和屏幕大小一致即可取消边框 
}

