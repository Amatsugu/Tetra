#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool isRunning;
const int width = 30;
const int height = 20;
int hX, hY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailLen;

enum Direction
{
	STOP = 0,
	LEFT, 
	RIGHT,
	UP,
	DOWN
};

Direction dir;

void Setup()
{
	isRunning = true;
	dir = STOP;
	score = 0;
	hX = width / 2;
	hY = height / 2;
	fruitX = (rand() % (width-2))+1;
	fruitY = (rand() % (height-2))+1;
}

void Draw()
{
	system("cls");
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
				cout << "*";
			else
			{
				if (x == hX && y == hY)
					cout << "0";
				else if (x == fruitX && y == fruitY)
					cout << "+";
				else
				{
					bool tail = false;
					for (int i = 0; i < tailLen; i++)
					{
						if (x == tailX[i] && y == tailY[i])
						{
							cout << "8";
							tail = true;
						}
					}
					if(!tail)
						cout << " ";
				}
			}

		}
		cout << endl;
	}
	cout << endl;
	cout << "Score: " + score;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'q':
				isRunning = false;
				break;
		}
	}
}

void Logic()
{
	for (int i = tailLen; i >= 0; i--)
	{
		if (i == 0)
		{
			tailX[i] = hX;
			tailY[i] = hY;
		}
		else
		{
			tailX[i] = tailX[i - 1];
			tailY[i] = tailY[i - 1];
		}
	}
	switch (dir)
	{
		case LEFT:
			hX--;
			break;
		case RIGHT:
			hX++;
			break;
		case UP:
			hY--;
			break;
		case DOWN:
			hY++;
			break;
		default:
			break;
	}
	if (hX > width || hX < 0 || hY > height || hY < 0)
		isRunning = false;
	if (hX == fruitX && hY == fruitY)
	{
		score++;
		fruitX = (rand() % (width - 2)) + 1;
		fruitY = (rand() % (height - 2)) + 1;
		tailLen++;
	}


}

int main()
{
	Setup();
	while (isRunning)
	{
		Draw();
		Input();
		Logic();
		cout << endl;
		cout << fruitX;
		cout << endl;
		cout << fruitY;
		Sleep(1u);
	}
	return 0;
}