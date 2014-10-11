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
	~Fabric(void);
	Fabric(Statistic* statistic);
	Snake* createSnake();
	Element* createBlank();
	Food* createFood();
	Wall* createWall();
	static Element* createSnakeElement(Snake* snake);
	Statistic* getStatistic();
private:
	Statistic* statistic;
	int keyCounter;
	void keyCount(Element* elem);
};