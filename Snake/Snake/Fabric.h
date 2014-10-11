#pragma once
#include "Snake.h"
#include "Statistic.h"
#include "Food.h"
#include "Wall.h"
#include "Element.h"


class Fabric
{
public:
	Fabric();
	Fabric(Statistic* statistic);
	Snake* createSnake();
	Food createFood();
	Wall createWall();
	static Element createSnakeElement(Snake* snake);
	~Fabric(void);
private:
	Statistic statistic;
	int widthKeys;
	int heightKeys;
	int keyCounter;
	void keyCount(Element* elem);
};