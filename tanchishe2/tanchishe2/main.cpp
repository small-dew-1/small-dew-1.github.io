#include<iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include<string>
#include <stdio.h>

#include "extern.h"
#include "gamefunction.h"
#include "gamerun.h"

using std::cout;
using std::endl;
using std::string;

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
				cout << "����������������룺";
			}
		} //��ʼ��Ϸ

		tosnakehead = new snake{ 0,0,nullptr };
		system("cls");
		initial(); //���ȳ�ʼ��
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

		delete tosnakehead; //һ����Ϸ����ɾ���ڴ�
	}

	gotoPos(0, height + 2);
	return 0;
}