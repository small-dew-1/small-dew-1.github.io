#ifndef EXTERN_H
#define EXTERN_H

struct snake
{
	int pointx;
	int pointy;
	snake* nextpoint; //ָ����һ������ڵ��ָ��
};//�����ߵ�����ڵ�

struct Food
{
	int x;
	int y;
}; //����ʳ�������

const int height = 30;
const int width = 30;    //��ͼ�ĸ߶ȿ��

extern int xspeed;
extern int yspeed; //���ƶ��ķ�����ٶȣ�Ĭ������

extern int maxscore;
extern int nowscore; //��ʷ��߷����͵�ǰ��߷���

extern snake* tosnakehead; //ָ����ͷ��λ�ã�ȫ�ֱ�����������Ҫ��
extern Food food; //ʳ��ȫ�ֱ��������Ե�����������

void gotoPos(int x, int y); //�ƶ���꺯�����ƶ�����ǰ��ͷ��λ��


#endif