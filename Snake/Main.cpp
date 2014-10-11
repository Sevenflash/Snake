// Snake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include "Snake.h"
#include "Statistic.h"
#include "Fabric.h"
#include "Field.h"

using namespace std;

void nextFrame(Field* field);

int _tmain(int argc, _TCHAR* argv[])
{
	Statistic* statistic = new Statistic();
	Fabric* fabric = new Fabric(statistic);
	Field field(20,20,2,fabric,statistic);

	int fps = 3;
	
	field.addElement(fabric->createFood());
	field.addSnake(fabric->createSnake());

	int keyDown;
	
	int clocks_per_frame = CLOCKS_PER_SEC/fps;
	int current_clock = 0, previous_clock = 0, delta_clock = 0;
	int start_clock = clock();

	int clocks_from_previous_update = 0;
	int current_loop_time = 0;
	int previous_loop_time = 0;
	int previous_update_clocks = 0;

	Snake* snake = field.getSnake();

	if(field.getDebugCounter() < field.getDebug()) {
		field.debugCounterUpdate();
		cout << "Screen #" << field.getDebugCounter() << endl;
		field.draw();
	}

	while(field.isGame()) {
		if(!field.isPause()) {
			previous_loop_time = current_loop_time;
			current_loop_time = clock();
			clocks_from_previous_update = current_loop_time - previous_update_clocks;
			
			if(clocks_from_previous_update >= clocks_per_frame) {
				previous_update_clocks = clock();
				nextFrame(&field);
			}
			bool directionChanged = false;
			if(kbhit() && !snake->directionChanged()) {
				keyDown = getch();
				if(keyDown == 72) snake->changeDirection(1);
				else if(keyDown == 77) snake->changeDirection(2);
				else if(keyDown == 80) snake->changeDirection(3);
				else if(keyDown == 75) snake->changeDirection(4);
			}
		}
	}

	int score = statistic->getUserScore();
	cout << "GAME OVER!" << endl;
	cout << "My score is 28 points." << endl;
	cout << "Your Score: " << score << " points." << endl;
	if(score<28) cout << "You lose :(" << endl;
	else cout << "Congratulations!" << endl;

	getch();
	cout << "Do you really want to exit? (Press \"ENTER\" to exit)" << endl;
	while(true) {
		int keyDown = getch();
		if(keyDown == 13) break;
	}

	/*
	Snake snake2 = fabric.createSnake();
	Snake snake3 = fabric.createSnake();

	cout << snake.getID() << endl;
	cout << snake2.getID() << endl;
	cout << snake3.getID() << endl;
	*/
	return 0;
}

void nextFrame(Field* field) {
	if(!field->getDebug()) {
		system("cls");
		field->update();
		field->draw();
	}
	else if(field->getDebugCounter() < field->getDebug()) {
		field->debugCounterUpdate();
		cout << "Screen #" << field->getDebugCounter() << endl;
		field->update();
		field->draw();
	}
}