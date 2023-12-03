#include "test.h"

 HBITMAP hw=NULL, hs = NULL, ha = NULL, hd = NULL, hf = NULL, hb = NULL, hh = NULL;
 HDC hdc=NULL, hMenDc=NULL, hTempDc=NULL;

 int map[40][40];
 char head;

 int hx, hy, ex, ey;

void initl(int map[40][40], char& head)
{
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 40; j++)
			map[i][j] = 0;

	 hx = rand() % 25 + 5, hy = rand() % 25 + 5;
	 ex = hx, ey = hy;
	map[hx][hy] = 2;
	int h = rand() % 4;
	if (h == 0)head = 'W';
	else if (h == 1) head = 'S';
	else if (h == 2) head = 'A';
	else if (h == 3) head = 'D';

}

void randfood()
{
	do
	{
		int i = rand() % 30+5, j = rand() % 30+5;
		if (map[i][j] != 1 && map[i][j] != 2)
		{
			map[i][j] = 3;
			break;
		}
	} while (1);
}

void display()
{
	PatBlt(hTempDc, 0, 0, 815, 815, WHITENESS);
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (map[i][j] == 2)
			{
				switch (head)
				{
				case 'W':
					SelectObject(hMenDc, hw);
					BitBlt(hTempDc, 20 * j, 20 * i, 20, 20, hMenDc, 0, 0, SRCCOPY);
					break;
				case 'S':
					SelectObject(hMenDc, hs);
					BitBlt(hTempDc, 20 * j, 20 * i, 20, 20, hMenDc, 0, 0, SRCCOPY);
					break;
				case 'A':
					SelectObject(hMenDc, ha);
					BitBlt(hTempDc, 20 * j, 20 * i, 20, 20, hMenDc, 0, 0, SRCCOPY);
					break;
				case 'D':
					SelectObject(hMenDc, hd);
					BitBlt(hTempDc, 20 * j, 20 * i, 20, 20, hMenDc, 0, 0, SRCCOPY);
					break;
				}
			}
			if (map[i][j] == 1)
			{
				SelectObject(hMenDc, hb);
				BitBlt(hTempDc, 20 * j, 20 * i, 20, 20, hMenDc, 0, 0, SRCCOPY);
			}
			if (map[i][j] == 3)
			{
				SelectObject(hMenDc, hf);
				BitBlt(hTempDc, 20 * j, 20 * i, 20, 20, hMenDc, 0, 0, SRCCOPY);
			}
		}
	}
}

int move()
{
	int is_eat = 0;     
	map[hx][hy] = 1;
	switch (head)
	{
	case 'W':         
		if (hx - 1 < 0 )        //判断是否出界,出界返回0as
			return 0;
		if (map[hx - 1][hy] == 3)               //判断是否吃到食物
			is_eat = 1;
		else if (map[hx - 1][hy] == 1 || map[hx - 1][hy] == 2)            //判断是否为身体,吃到返回0
			return 0;
		map[hx - 1][hy] = 2;
		hx = hx - 1;
		break;
	case 'A':
		if (hy - 1 <0)        //判断是否出界,出界返回0
			return 0;
		if(map[hx][hy - 1] == 3)               //判断是否吃到食物
			is_eat = 1;
		else if (map[hx][hy-1] == 1 || map[hx ][hy-1] == 2)            //判断是否为身体,吃到返回0
			return 0;
		map[hx][hy-1] = 2;
		hy = hy - 1;
		break;
	case 'S':
		if (hx + 1 >= 40)        //判断是否出界,出界返回0
			return 0;
		if (map[hx+1][hy] == 3)               //判断是否吃到食物
			is_eat = 1;
		else if (map[hx + 1][hy] == 1 || map[hx + 1][hy] == 2)            //判断是否为身体,吃到返回0
			return 0;
 		map[hx + 1][hy] = 2;
		hx = hx + 1;
		break;
	case 'D':
		if (hy + 1 >= 40)        //判断是否出界,出界返回0
			return 0;
		if (map[hx][hy + 1] == 3)               //判断是否吃到食物
			is_eat = 1;
		else if (map[hx][hy+1] == 1 || map[hx][hy+1] == 2)            //判断是否为身体,吃到返回0
			return 0;
		map[hx][hy+1] = 2;
		hy = hy + 1;
		break;
	}
	if (!is_eat)           //没吃到尾更新
	{
		map[ex][ey] = 0;
		if (map[ex + 1][ey] == 1 || map[ex + 1][ey] == 2)
			ex = ex + 1;
		else if (map[ex - 1][ey] == 1 || map[ex - 1][ey] == 2)
			ex = ex - 1;
		else if (map[ex][ey + 1] == 1 || map[ex][ey + 1] == 2)
			ey = ey + 1;
		else if (map[ex][ey - 1] == 1 || map[ex][ey - 1] == 2)
			ey = ey - 1;
	}
	else if(is_eat)               //吃到尾不变，随机生成食物
	{
		map[ex][ey] = 1;
		randfood();
	}
}
