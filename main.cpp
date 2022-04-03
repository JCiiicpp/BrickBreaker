#include <graphics.h>
#include <ctime>
#include <iostream>
#include <cassert>
#include "classA.h"
#include "public.h"
#include "System.h"
#include <Windows.h>
using namespace std;


//
//class Realize
//{
//
//private:
//
//
//public:
//	
////����ľ��
//void drawBoard(Board* pBoard);
//
////��ʼ����ͼ
//void initMap(int map[][8], int row, int cols);
//
////����ľ�������ƶ�
//void keyDown(Board* pBoard);
//
////����ש��
//void drawMap(int map[][8], int row, int cols);
//
////������
//void drawBall(Ball* pBall);
//
////�ƶ���
//void moveBall(Ball* pBall, Board* pBaord, int map[][8],int row,int cols);
//
////��ʱ��
//int Timer(int duration, int id);
//
//};
// 
//����ľ��



//int main()
//{
//	srand((unsigned int)time(NULL));
//	initgraph(800, 600);
//	int map[5][8];
//	Board* pBoard = createBoard(300, 600 - 25, 200, 25, WHITE);
//	 Ball* pBall = createBall(400, 300, 10, 5, -5, RED);
//	initMap(map, 5, 8);
//	BeginBatchDraw();
//	while (1)
//	{
//
//		cleardevice();	//����
//		drawMap(map, 5, 8);
//		drawBoard(pBoard);
//		drawBall(pBall);
//		if (Timer(20, 0))
//			moveBall(pBall, pBoard, map, 5, 8);
//		keyDown(pBoard);
//		//Sleep(10);		//����ͣ��20����
//		if (gameOver(pBall, pBoard))
//		{
//			outtextxyInfo(300, 350, "������!.....");
//			FlushBatchDraw();
//			break;
//		}
//		if (windGame(map, 5, 8))
//		{
//			outtextxyInfo(300, 350, "��Ӯ��!.....");
//			FlushBatchDraw();
//			break;
//		}
//		FlushBatchDraw();   //��ʾ�Ѿ����õ�
//	}
//	Sleep(5000);
//	EndBatchDraw();         //������FlushBatchDraw ֻ��EndBatchDraw�������ʾ
//	//��ʾ
//	closegraph();
//	return 0;
//}


class Board
{
public:
	int x;
	int y;
	int w;
	int h;
	COLORREF color;
};

class Board* createBoard(int x, int y, int w, int h, COLORREF color)
{
	Board* board = new Board;
	assert(board);
	board->x = x;
	board->y = y;
	board->w = w;
	board->h = h;
	board->color = color;
	return board;
}

class Ball
{
public:
	int x;
	int y;
	int r;
	int dx;
	int dy;
	unsigned long color;
};

class Ball* createBall(int x, int y, int r, int dx, int dy, unsigned long color)
{
	Ball* pBall = new Ball;
	assert(pBall);
	pBall->x = x;
	pBall->y = y;
	pBall->r = r;
	pBall->dx = dx;
	pBall->dy = dy;
	pBall->color = color;
	return pBall;
}

class Map
{
public:
	Map() {}
	
	//��ʼ����ͼ
	void initMap(int map[][8], int row, int cols);
	//���Ƶ�ͼ
	void drawMap(int map[][8], int row, int cols);
	//����ľ��
	void drawBoard(Board* pBoard);
	//������
	void drawBall(Ball* pBall);
};



class Move
{
public:
	
	//�ƶ���
	void moveBall(Ball* pBall, Board* pBaord, int map[][8], int row, int cols);
	//�����ľ���
	int hitBoard(Ball* pBall, Board* pBoard);
	//�����ǽ��
	int hitBricks(Ball* pBall, int map[][8], int row, int cols);
};


class System
{
public:
	//��������,����ľ��������
	void keyDown(Board* pBoard);

	//��ʱ��
	int Timer(int duration, int id);

	//��Ϸ����
	int gameOver(Ball* pBall, Board* pBoard);

	//��Ϸ������������ʾ
	void outtextxyInfo(int x, int y, const char* info);

	//��Ϸʤ��
	int windGame(int map[][8], int row, int cols);

};

void Map::drawBoard(Board* pBoard)
{
	setfillcolor(pBoard->color);
	//ľ���x , y ���� , ľ���������� ��� �͸߶� 
	solidrectangle(pBoard->x, pBoard->y, pBoard->x + pBoard->w, pBoard->y + pBoard->h);
}

void Map::initMap(int map[][8], int row, int cols)
{
	for (int i = 0; i < row; i++) 

	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = rand() % 3 + 1; //[1,3]
		}
	}
}

void Map::drawMap(int map[][8], int row, int cols)
{
	setlinecolor(BLACK);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int x = 100 * j;
			int y = 25 * i;
			switch (map[i][j])
			{
			case 0:
				break;
			case 1:
				setfillcolor(RGB(255, 255, 85));
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 2:
				setfillcolor(RGB(85, 255, 85));
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 3:
				setfillcolor(RGB(85, 85, 255));
				fillrectangle(x, y, x + 100, y + 25);
				break;
			}
		}
	}
}

void System::keyDown(Board* pBoard) 
{
	//�޸�ľ�������
	//_getch()
	//ʹ���첽������ , ��������
	if((GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) && pBoard->x > 0) 
	{
		pBoard->x -= 1;
	}
	if((GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))&& pBoard->x + pBoard->w < 800) 
	{
		pBoard->x += 1;
	}
}

void Map::drawBall(Ball* pBall) 
{
	//setfillcolor(pBall->color);
	setfillcolor(RGB(rand() % 255, rand() % 255 , rand() % 255)); //�����ɫ
	solidcircle(pBall->x, pBall->y, pBall->r);
}

void Move::moveBall(Ball* pBall, Board* pBoard, int map[][8], int row, int cols) 
{
	//��ײ����, 
	/*if(pBall->x - pBall->r <= 0 || pBall->x + pBall->r >= 800) 
	{
		pBall->dx = -pBall->dx;
	}

	if(pBall->y - pBall->r <= 0 || pBall->y + pBall->r >=600 ) 
	{
		pBall->dy = -pBall->dy;
	}*/
	
	if (pBall->x - pBall->r <= 0 || pBall->x + pBall->r >= 800)
	{
		pBall->dx = -pBall->dx;
	}

#if 0
	if (pBall->y - pBall->r <= 0 || hitBoard(pBall, pBoard))
	{
		cout << "������ײ" << endl;
		cout << "û�з�������" << endl;
		pBall->dy = -pBall->dy;
	}
#else
	if(pBall->y - pBall->r <= 0 
	|| pBall->y + pBall->r >= 600 
	|| hitBoard(pBall,pBoard)
	|| hitBricks(pBall,map,row,cols))
	{
		cout << "������ײ" << endl;
		pBall->dy = -pBall->dy;
	}
#endif
	pBall->x += pBall->dx;
	pBall->y += pBall->dy;
	 
}

int System::Timer (int duration,int id) 
{
	static int startTime[10];	//��̬�����Զ���ʼ��Ϊ��
	//�þ�̬��������ΪҪ��¼��һ�ε����н��

	int endTime = clock();
	if(endTime - startTime[id] >= duration) 
	{
		//��һ�ο�ʼ��ʱ���̱��һ�ν�����ʱ��
		startTime[id] = endTime;
		return 1;
	}
	return 0;
}

int Move::hitBoard(Ball* pBall, Board* pBoard)
{

#if 0
	if(pBall->y + pBall->r == pBoard->y) 
	{
		if(pBall->x > pBoard->x && pBall->x < pBoard->x + pBoard->w) 
		{
			cout << "������ײ" << endl;
			return 1;
		}
		else 
		{
			cout << "��ײ����" << endl;
		}
	}
#else
	if (pBall->y + pBall->r == pBoard->y)
	{
		if (pBall->x > pBoard->x && pBall->x <= pBoard->x + pBoard->w)
		{
			cout << "������ײ" << endl;
			return 1;
		}
		else
		{
			cout << "��ײ����" << endl;
		}
	}
#endif

	return 0;
}

int Move::hitBricks(Ball* pBall,int map[][8],int row,int cols)
{
	int j = pBall->x / 100;
	int i = (pBall->y - pBall->r) / 25;
	if(i < row && j < cols && map[i][j] != 0) 
	{
		map[i][j] = 0;
		return 1;
	}
	return 0;
}

int System::gameOver(Ball* pBall,Board* pBoard)
{
	if(pBall->y + pBall->r > pBoard->y) 
	{
		return 1;
	}
	return 0;
}

int System::windGame(int map[][8], int row, int cols)
{
	for(int i = 0; i < row; ++i) 
	{
		for(int j = 0; j < cols; ++j) 
		{
			if(map[i][j] !=0) 
			{
				return 0;
			}
		}
	}
	return 1;
}

void System::outtextxyInfo(int x, int y, const char* info)
{
	settextstyle(45, 0, "����");
	settextcolor(RED);
	outtextxy(x, y, info);
}

int main() 
{
	Map init;
	Move move;
	System psystem;
	System judge;
	srand((unsigned int)time(NULL));
	initgraph(800, 600);
	int map[5][8];
	Board* pBoard = createBoard(300, 600 - 25, 200, 25, BLUE);
	Ball* pBall = createBall(400, 300, 10, 15, -5, RED);
	init.initMap(map, 5, 8);
	BeginBatchDraw();
	while (true)
	{ 
		cleardevice();	
		init.drawMap(map, 5, 8);
		init.drawBoard(pBoard);
		init.drawBall(pBall);
		if (judge.Timer(20, 0))
			move.moveBall(pBall, pBoard, map, 5, 8);
		judge.keyDown(pBoard);
		//Sleep(10);		
		if (judge.gameOver(pBall, pBoard)) 
		{
			psystem.outtextxyInfo(300, 350, "��Ϸʧ��");
			FlushBatchDraw();
			break;
		}
		if (judge.windGame(map, 5, 8)) 
		{
			psystem.outtextxyInfo(300, 350, "��Ϸʤ��");
			FlushBatchDraw();
			break;
		}
		FlushBatchDraw();   
	}
	Sleep(5000);
	EndBatchDraw();         
	
	closegraph();
	return 0;
}