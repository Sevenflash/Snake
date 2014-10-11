#pragma once
#include <iostream>
#include "SnakeElement.h"

class Snake
{
public:
	const static int startSize=3;
	Element** elems;
	int numberSnake;
	void setID(int number);
	int getID();
	void draw();
	void update();
	SnakeElement* getLastElement();
	SnakeElement* createHead();
	SnakeElement* createBody();
	bool snakeElements();
	bool isElements();
	Snake(void);
	~Snake(void);
private:
	int snakeID;
	int posx;
	int posy;
	int direction; // 1 - top, 2 - right, 3 - down, 4 - left;
	Element* getHead();
	void Snake::swap(int x1, int y1, int x2, int y2);
	Element* getElems();
	int countElems();
};