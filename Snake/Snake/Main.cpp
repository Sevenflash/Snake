// Snake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "Snake.h"
#include "Statistic.h"
#include "Fabric.h"
#include "GlobalClass.h"
#include "Field.h"

using namespace std;

void NextFrame();

int _tmain(int argc, _TCHAR* argv[])
{
	Statistic* pStatistic = new Statistic();
	Fabric* pFabric = new Fabric(pStatistic);
	Field field(10,10,2, pFabric);
	//Field::selfLink = &field;
	Fabric oFabric = *pFabric;

	int fps = 60;

	/*
	float mspf = (float)1000/fps;
	float clpms = (float)CLOCKS_PER_SEC/1000;
	float clpf = mspf*clpms;
	*/
	float clpf = (float)CLOCKS_PER_SEC/fps;
	int tclock, sclock, eclock, uclock;
	sclock = clock();
	uclock = 0;
	//cout << clpf << endl;
	/*
	int tclock, sclock, eclock;
	sclock = clock();
	for(int i=0;i<1000;i++) {
		cout << "do" << endl;
	}
	eclock = clock();
	tclock = eclock - sclock;
	cout << sclock << endl;
	cout << eclock << endl;
	cout << tclock << endl;
	*/
	
	//1 - food, 2 - snake, 3 - food.
	field.addElement(oFabric.createFood());
	field.addElement(oFabric.createWall());

	field.addSnake(oFabric.createSnake());

	float bclock=0;
	while(true) {
		eclock = clock();
		tclock = eclock - sclock - uclock;
		
		if(bclock==clpf) {
			system("cls");
			field.update();
			field.draw();
		}
		else if(bclock<clpf) {
			bclock += tclock;
		} 
		else if(bclock>clpf) {
			system("cls");
			field.update();
			field.draw();
			bclock = bclock - clpf;
		}

		uclock = eclock;
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