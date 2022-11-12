#ifndef EXTERN_H
#define EXTERN_H

struct snake
{
	int pointx;
	int pointy;
	snake* nextpoint; //指向下一个身体节点的指针
};//定义蛇的身体节点

struct Food
{
	int x;
	int y;
}; //定义食物的坐标

const int height = 30;
const int width = 30;    //地图的高度宽度

extern int xspeed;
extern int yspeed; //蛇移动的方向和速度，默认向上

extern int maxscore;
extern int nowscore; //历史最高分数和当前最高分数

extern snake* tosnakehead; //指向蛇头的位置，全局变量，函数都要用
extern Food food; //食物全局变量，被吃掉就重新生成

void gotoPos(int x, int y); //移动光标函数，移动到当前蛇头的位置


#endif