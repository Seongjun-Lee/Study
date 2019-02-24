#include <iostream>
#include <conio.h>

using namespace std;

typedef struct POINT
{
	int x;
	int y;
}POINT, *PPOINT;

void setMaze(char maze[10][10], PPOINT userpos, PPOINT startpos, PPOINT endpos)
{

	startpos->x = 0;
	startpos->y = 0;

	endpos->x = 8;
	endpos->y = 9;

	*userpos = *startpos;
	strcpy_s(maze[0], "211100000");
	strcpy_s(maze[1], "000111000");
	strcpy_s(maze[2], "011101111");
	strcpy_s(maze[3], "010000010");
	strcpy_s(maze[4], "011100011");
	strcpy_s(maze[5], "000111001");
	strcpy_s(maze[6], "011100011");
	strcpy_s(maze[7], "010100110");
	strcpy_s(maze[8], "011100100");
	strcpy_s(maze[9], "000000113");
}

void print(char maze[10][10], PPOINT userpos)
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (userpos->x == j && userpos->y == i)
				cout << "●";
			else if (maze[i][j] == '2')
				cout << "☆";
			else if (maze[i][j] == '0')
				cout << "■";
			else if (maze[i][j] == '3')
				cout << "★";
			else if(maze[i][j] == '1')
				cout << "  ";
		}
		cout << endl;
	}
}

void move(char maze[10][10], PPOINT userpos, char choice)
{
	switch (choice)
	{
	case 'w':
	case 'W':
		if (userpos->y - 1 >= 0)
		{
			if (maze[userpos->y - 1][userpos->x] != '0')
			{
				--userpos->y;
			}
		}
		break;
	case 's':
	case 'S':
		if (userpos->y + 1 < 10)
		{
			if (maze[userpos->y + 1][userpos->x] != '0')
			{
				++userpos->y;
			}
		}
		break;
	case 'a':
	case 'A':
		if (userpos->x - 1 >= 0)
		{
			if (maze[userpos->y][userpos->x-1] != '0')
			{
				--userpos->x;
			}
		}
		break;
	case 'd':
	case 'D':
		if (userpos->x + 1 < 9)
		{
			if (maze[userpos->y][userpos->x+1] != '0')
			{
				++userpos->x;
			}
		}
		break;
	}
}

void main()
{
	char maze[10][10];

	POINT pos, startpos, endpos;
	setMaze(maze, &pos, &startpos, &endpos);

	while (true)
	{
		system("cls");
		print(maze, &pos);
		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료 : ";
		char choice = _getch();

		if (choice == 'q' || choice == 'Q')
			break;

		move(maze, &pos, choice);

		if (pos.x == endpos.x && pos.y == endpos.y)
			break;
	}

	getchar();
	getchar();
}