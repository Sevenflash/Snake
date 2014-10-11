#include "StdAfx.h"
#include "Fabric.h"
#include "Statistic.h"
#include "Snake.h"
#include "GlobalClass.h"
#include "Field.h"
#include "SnakeElement.h"

Snake* Fabric::createSnake() {
	Snake* psnake = new Snake();
	//Snake snakeObject = *snake;
	int numberSnake = Fabric::statistic.getNumberSnakes()+1;
	Fabric::statistic.setNumberSnakes(numberSnake);
	(*psnake).setID(numberSnake);
	return psnake;
}

Element Fabric::createSnakeElement(Snake* snake) {
		Element* snakePart = new SnakeElement();
		Snake oSnake = *snake;
		Element oSnakePart = *snakePart;
		if(oSnake.isElements()) oSnakePart.snakeElementType = 2;
		else oSnakePart.snakeElementType = 1;
		oSnakePart.last = true; // del
		return oSnakePart;
}

Food Fabric::createFood() {
	Food* food = new Food();
	return *food;
}

Wall Fabric::createWall() {
	Wall* wall = new Wall();
	return *wall;
}

Fabric::Fabric(Statistic* statistic)
{
	Fabric::statistic = *statistic;
}

Fabric::Fabric(void) {
	Fabric::keyCounter = 0;
}

Fabric::~Fabric(void)
{
}
