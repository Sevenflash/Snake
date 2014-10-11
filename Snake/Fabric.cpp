#include "StdAfx.h"
#include "Fabric.h"
#include "Statistic.h"
#include "Snake.h"
#include "Field.h"
#include "SnakeElement.h"

Snake* Fabric::createSnake() {
	Snake* snake = new Snake();
	int numberSnake = Fabric::statistic->getNumberSnakes()+1;
	Fabric::statistic->setNumberSnakes(numberSnake);
	snake->setID(numberSnake);
	return snake;
}

Element* Fabric::createBlank() {
	Element* blankElement = new Element();
	return blankElement;
}


Element* Fabric::createSnakeElement(Snake* snake) {
		Element* snakePart = new SnakeElement();
		if(!snake->isElements()) snakePart->setAsHead();
		return snakePart;
}

Food* Fabric::createFood() {
	Food* food = new Food();
	return food;
}

Wall* Fabric::createWall() {
	Wall* wall = new Wall();
	return wall;
}

Fabric::Fabric(Statistic* statistic)
{
	Fabric::statistic = statistic;
}

Fabric::Fabric(void) {
	Fabric::keyCounter = 0;
}

Fabric::~Fabric(void)
{
}

Statistic* Fabric::getStatistic() {
	return Fabric::statistic;
}