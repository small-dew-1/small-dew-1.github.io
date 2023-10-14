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
	snake* nextpoint; //ָ����һ������ڵ��ָ��
	snake(int x=0,int y=0,snake* p=nullptr):pointx(x),pointy(y),nextpoint(p){}
};//�����ߵ�����ڵ㣨��������ʽ���壩 

struct Food
{
	int x;
	int y;
}; //����ʳ�������

int height = 28;
int width = 28;    //��ͼ�ĸ߶ȿ��,Ĭ��Ϊ���

int xspeed;
int yspeed;//���ƶ��ķ�����ٶȣ�Ĭ������

string maplarge="large";//���ڼ�¼��ʼ�ĵ�ͼ�ߴ�
int mapgrade=0;
int grade = 1;//���ڼ�¼�ȼ�

int maxscore[2][3]= {0,0,0,0,0,0};
int nowscore[2][3]= {0,0,0,0,0,0};//��ʷ��߷����͵�ǰ��߷���

snake* tosnakehead;//ָ����ͷ��λ�ã�ȫ�ֱ�����������Ҫ��
Food food = { 0,0 };//ʳ��ȫ�ֱ��������Ե�����������

void gotoPos(int x, int y); //�ƶ���꺯�����ƶ�����ǰ��ͷ��λ��
void printmenu(); //��ʼʱ��ӡ���˵�
void initial(); //��ʼ����Ϸ��������Ϸ��ͼ����ͷ��ʳ�Ｐ��λ��)
void printmap(); //������Ϸ��ͼ
void printsnake(); //��ӡ����ʼ�ߵ�λ�ã�����ֻ��Ҫ�޸�ͷβ���ɣ�
void printfood(); //�������ʳ��
void addhead(int x, int y); //�����ͷ���Ѿ���ͷ�������
void deletetail(); //ɾ����β
bool eatfood(); //�ж��Ƿ�Ե�ʳ��
void move(); //�ص㺯���������ߵ��ƶ���ز��������ķ��򣬸�����λ�ã��ж��Ƿ�Ե�ʳ��
bool hitwall(); //�ж��Ƿ�ײǽ��������Ϸ������־
void freelist(); //��Ϸ����ʱҪ������п��ٿռ䣬��ֹ�ڴ�й©
void gameover(); //������Ϸ������������
void pause();//����ʵ����Ϸ��ͣ
void back_to_menu();//���ڷ��ز˵�
void preserve();//������Ϸ��¼
void showmaxscore();//������ʷ��߷�
void changemap();//ѡ���ͼ��С 
void printmaxscore();//��ʾ��߷��� 
void changegrade();//ѡ���Ѷ�
void restart();//�������¿�ʼ 
void screen();//���ڹ̶�����
void ptr();//�������ع��
void noroller();//����ɾ������

int main()
{
	screen();
	ptr();
	noroller();
	while (1)
	{
		system("cls");
		showmaxscore();
		printmenu();   //��ӡ�˵�

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
				
		} //��ʼ��Ϸ
		
		tosnakehead = new snake(0,0, nullptr);
		system("cls");
		initial(); //���ȳ�ʼ��
		Sleep(3000); //�������3�룬3�����Ϸ���Զ���ʼ�����Ըĳ���ͣ���ܣ�
		
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

		delete tosnakehead; //һ����Ϸ����ɾ���ڴ�
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
	SetConsoleCursorPosition(hout, cor); //���ù��λ��
}//�ƶ���꺯�����ƶ�����ǰ��ͷ��λ��

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
}//������߷� 

void printmaxscore(){
	system("cls");
	cout << "�Ѷ�1����ͼ����߷�" << maxscore[0][0] <<endl;
	cout << "�Ѷ�1����ͼ����߷�" << maxscore[0][1] <<endl;
	cout << "�Ѷ�1����ͼС��߷�" << maxscore[0][2] <<endl;
	cout << "�Ѷ�2����ͼ����߷�" << maxscore[1][0]<<endl;
	cout << "�Ѷ�2����ͼ����߷�" << maxscore[1][1]<<endl;
	cout << "�Ѷ�2����ͼС��߷�" << maxscore[1][2]<<endl;
	cout << "����Q�˳�" << endl;
	
	char a1;
	while (1)
	{
		a1 = _getch();
		if (a1 == 'q' || a1 == 'Q')
			break;
	}
}//��ʾ��߷��� 

void changegrade(){
	system("cls");
	cout << "��ѡ���Ѷȴ�С ��" << endl << "����1  �Ѷ�1" << endl << "����2  �Ѷ�2" << endl;
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
}//ѡ���Ѷ�

void printmenu()
{
	cout << "��ӭ����̰����С��Ϸ" << endl;
	cout << "����G�鿴��ʷ��߷�" << endl; 
	cout << "����Nѡ���ͼ��С����ǰ��ͼ��С��" << maplarge << endl;
	cout << "����Mѡ���Ѷȵȼ����ٶȴ�С������ǰ�Ѷȵȼ���" << grade << endl;
	cout << "����E ��ʼ��Ϸ" <<endl<< "����Q ������Ϸ" << endl;

} //��ʼʱ��ӡ���˵�

void changemap(){
	system("cls");
	cout << "��ѡ���ͼ��С ��" << endl << "����L  ���ɴ��ͼ" << endl << "����M  �����е�ͼ" << endl <<"����S  С��ͼ"<<endl;
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
}//�޸ĵ�ͼ��С 

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
	
	gotoPos(2*width+15, height / 2-2);
	cout << "����ESC ��ͣ��Ϸ�����������������Ϸ";
	gotoPos(2*width+15,height/2+2);
	cout << "����M ���ز˵�";
	gotoPos(2 * width + 15, height / 2 + 6);
	cout << "����R���¿�ʼ";
}// ������Ϸ��ͼ

void printsnake()
{
	snake* snakehead = new snake(width,height/2,nullptr); //������ͷ 
	tosnakehead->nextpoint = snakehead; //ȫ�ֱ���ָ����ͷ 
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
	yspeed = 1;
	nowscore[grade-1][mapgrade] = 0;
	printmap();
	printsnake();
	printfood();

}//��ʼ����Ϸ��������Ϸ��ͼ����ͷ��ʳ�Ｐ��λ��)

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
			back_to_menu();//����M�󷵻ز˵�,�����˳���Ϸ���¿�ʼ���� 
			break;
		}
		
		case 27:
		{
			pause(); //ִ����ͣ����
			break;
		}//ע�⣺��ͷ���ܵ�ͷ��ֻ��ת��
		
		case 82:case 114:
		{
			restart();
			break;
		}//�������¿�ʼ
		
		}
		
		}
		
	//������ͷ
	addhead(tosnakehead->nextpoint->pointx + xspeed, tosnakehead->nextpoint->pointy + yspeed);
	
	//�ж��Ƿ�Ҫɾ����β��ִ��
	if (eatfood())
	{
		nowscore[grade-1][mapgrade]++; //�ӷ�
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
	cout << "Your Score: " << nowscore[grade-1][mapgrade] <<endl;

	if (maxscore[grade-1][mapgrade] < nowscore[grade-1][mapgrade]) maxscore[grade-1][mapgrade] = nowscore[grade-1][mapgrade];
	cout << "����������ز˵�ѡ��";
	system("pause>nul");
	freelist();
} //������Ϸ������������

void pause()
{
	system("pause>nul");
}

void back_to_menu()
{
	system("cls");
	freelist();
	delete tosnakehead; 
	main();      //���ڷ��ز˵�
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
	system("cls");//������
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
	main();      //���ڷ��ز˵�
}
void screen()    //���ڹ̶�̰���߽����С�Լ�ɾ�������С��
{
	SetWindowLongPtrA(
		GetForegroundWindow(),
		GWL_STYLE,
		GetWindowLongPtrA(GetForegroundWindow(), GWL_STYLE)
		& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX           //ɾ�������С���Լ���С����
	);
}
void ptr()   //�������ع��
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//����һ�����ṹ�壬ǰһ��ֵΪ����size��int������һ��ֵΪ���Ŀɼ��ԣ�bool��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info); //�����ṹ��Ӧ�õ�����̨����ϣ��Ӷ����ع��
}
void noroller()            //����ɾ������
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	SMALL_RECT rect = csbiInfo.srWindow;     //ȡ�ô��ڵ����ϽǺ����½ǵ�����
	COORD size = { rect.Right + 1 ,rect.Bottom + 1 };	//ȡ�����½�����+1��λ�� 
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);  //���建������С�����ֻ�������С����Ļ��Сһ�¼���ȡ���߿� 
}

