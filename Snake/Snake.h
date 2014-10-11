#pragma once
#include <iostream>
#include "SnakeElement.h"

enum Direction 
{
	edUp, edDown
};

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
	bool snakeElements();
	bool isElements();
	void changeDirection(int d);
	int countElems();
	bool directionChanged();
	Snake(void);
	~Snake(void);
private:
	int snakeID;
	int posx;
	int posy;
	int direction; // 1 - top, 2 - right, 3 - down, 4 - left;
	bool flagDirectionChanged;
	Element* getHead();
	void Snake::swap(int x1, int y1, int x2, int y2);
	Element* getElems();
};