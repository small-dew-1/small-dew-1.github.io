#include<iostream>
#include <windows.h>
#include<string>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#include "gamerun.h"
#include "extern.h"

using std::cout;
using std::endl;
using std::string;

void printmap()
{
	int i, j;
	for (i = 0; i <=2*(width + 1); i+=2)
	{
		gotoPos(i, 0);
		cout << "��";

		gotoPos(i, height + 1);
		cout << "��";
	}

	for (i = 0; i <= height+1; i++)
	{
		gotoPos(0,i);
		cout << "��";
		
		gotoPos(2*(width+1), i);
		cout << "��";
	}

	for(i=2;i<=2*width;i+=2)
	{
		for(j=1;j<=height;j++)
		{
			gotoPos(i, j);
			cout << "��";
		}
	}
}// ������Ϸ��ͼ

void printsnake()
{
	snake* snakehead = new snake{ 20,11,nullptr };
	tosnakehead->nextpoint = snakehead;
	gotoPos(snakehead->pointx, snakehead->pointy);
	cout << "��";
} //��ӡ����ʼ�ߵ�λ�ã�����ֻ��Ҫ�޸�ͷβ���ɣ�

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
			}//�ж��Ƿ������غϣ��غ���������
		}

		if (t == 0)
		{
			gotoPos(food.x, food.y);
			cout << "��";
			break;
		}
	}
} //�������ʳ��

void initial()
{
	xspeed = 0;
	yspeed = -1;
	nowscore = 0;
	printmap();
	printsnake();
	printfood();
}

void addhead(int x, int y)
{
	snake* newhead = new snake{ x,y,tosnakehead->nextpoint }; //��������ͷ
	gotoPos(tosnakehead->nextpoint->pointx, tosnakehead->nextpoint->pointy);
	cout << "��";//���ľ���ͷ
	tosnakehead->nextpoint = newhead;
	gotoPos(tosnakehead->nextpoint->pointx, tosnakehead->nextpoint->pointy);
	cout << "��";//�������ͷ
} //�����ͷ���Ѿ���ͷ�������

void deletetail()
{
	snake* p = tosnakehead;
	while (p->nextpoint->nextpoint != nullptr) {
		p = p->nextpoint;
	}//��λ����βǰһ��
	snake* p1 = p;
	p1 = p1->nextpoint; //��λ����β
	p->nextpoint = nullptr;  //��������β
	gotoPos(p1->pointx, p1->pointy);
	cout << "��";

	delete p1;  //ɾ����β
} //ɾ����β 

bool eatfood()
{
	if (tosnakehead->nextpoint->pointx == food.x && tosnakehead->nextpoint->pointy == food.y)
	{
		return true;
	}
	else {
		return false;
	}
} //�ж��Ƿ�Ե�ʳ��

void move()
{
	//�ı䷽��
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
		}//ע�⣺��ͷ���ܵ�ͷ��ֻ��ת��
	}

	//������ͷ
	addhead(tosnakehead->nextpoint->pointx + xspeed, tosnakehead->nextpoint->pointy + yspeed);

	//�ж��Ƿ�Ҫɾ����β��ִ��
	if (eatfood())
	{
		nowscore++; //�ӷ�
		printfood();
	}
	else {
		deletetail();
	}

} //�ص㺯���������ߵ��ƶ���ز��������ķ��򣬸�����λ�ã��ж��Ƿ�Ե�ʳ��

bool hitwall()
{
	if (tosnakehead->nextpoint->pointx == 0 || tosnakehead->nextpoint->pointx == 2*(width + 1) ||
		tosnakehead->nextpoint->pointy == 0 || tosnakehead->nextpoint->pointy == height + 1) {
		return true;
	} //�Ƿ���ǽ����

	snake* p = tosnakehead->nextpoint;
	while (p->nextpoint != nullptr)
	{
		p = p->nextpoint;
		if (p->pointx == tosnakehead->nextpoint->pointx && p->pointy == tosnakehead->nextpoint->pointy)
		{
			return true;
		}
	} //�Ƿ�����������

	return false;
} //�ж��Ƿ�ײǽ��������Ϸ������־

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
} //��Ϸ����ʱҪ������п��ٿռ䣬��ֹ�ڴ�й©

void gameover()
{
	system("cls");
	cout << "Game Over" << endl;
	cout << "Your Score: " << nowscore << endl;

	if (maxscore < nowscore) maxscore = nowscore;

	freelist();
} //������Ϸ������������