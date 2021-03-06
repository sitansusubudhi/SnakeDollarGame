#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, moneyX, moneyY, score;
int tailX[100], tailY[100];
int nTail;
enum class direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;

void Setup() {
	srand(time(NULL));
	gameOver = false;
	dir = direction::STOP;
	x = width / 2;
	y = height / 2;
	moneyX = 1 + rand() % (width - 1 + 1);	//Generate within range 1 to 20
	moneyY = 1 + rand() % (height - 1 + 1);
	score = 0;
}

void Draw() {
	system("cls"); //system("clear");

	

	//Side borders
	for (int i = 0; i < height+2; i++) {
		for (int j = 0; j < width+2; j++) {
			if (j == 0 || j == width + 1 || i == 0 || i == height + 1) {
				cout << "#";
			}
			else if (i == y && j == x) {	//i = height co-ordinate
				cout << "O";
			}
			else if (i == moneyY && j == moneyX) {
				cout << "$";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if(!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	
	cout << endl;
	cout << "Score = " << score << endl;
	cout << "moneyX : " << moneyX;
	cout << " moneyY : " << moneyY << endl;
	cout << "x : " << x << " y : " << y;
	cout << endl;
}

void Input() {
	if (_kbhit) {	//Keyboard key pressed returns 1 else 0
		switch (_getch()) {	//getch returns ASCII value of character pressed
		case 'a': 
		case 'A':
			dir = direction::LEFT;
			break;
	    case 'd':
		case 'D':
			dir = direction::RIGHT;
			break;
		case 'w':
		case 'W':
			dir = direction::UP;
			break;
		case 's':
		case 'S':
			dir = direction::DOWN;
			break;
		case 'x':
		case 'X':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	
	
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {
	case direction::LEFT:
			x--;
			if (x == 0) x = width;		    //WRAP-AROUND
		break;
	case direction::RIGHT:
		x++; 
		if (x == width + 1) x = 1;		//WRAP-AROUND
		break;
	case direction::UP:
		y--;
		if (y == 0) y = height;			//WRAP-AROUND
		break;
	case direction::DOWN:
		y++;
		if (y == height + 1) y = 1;		//WRAP-AROUND
		break;
	default:
		break;
	}

	//MODIFIED 
	if (x > width || x <= 0 || y <= 0 || y > height) {	//If we touch the wall game is over
		gameOver = true;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == moneyX && y == moneyY) {
		score += 10;
		srand(time(NULL));

		moneyX = 1 + rand() % (width-1 + 1);	//Generate within range 1 to 20
		moneyY = 1 + rand() % (height-1 + 1);
		nTail++;
	}

}

int main()
{
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(10);
	}

	/*while (!gameOver) {
	x = rand() % 20;
	cout << x << endl;
	}*/

	//cout << "Hello World";
	cout << endl;
	return 0;
}


