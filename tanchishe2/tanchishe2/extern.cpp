#include <iostream>
#include <Windows.h>
#include "extern.h"

using std::cout;
using std::string;

int xspeed;
int yspeed;

int maxscore = 0;
int nowscore = 0;

snake* tosnakehead;
Food food = { 0,0 };

void gotoPos(int x, int y) {
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor); //���ù��λ��
}//�ƶ���꺯�����ƶ�����ǰ��ͷ��λ��
