#include "StdAfx.h"
#include "Field.h"
#include "Element.h"
#include "Food.h"
#include "Snake.h"
#include "SnakeElement.h"
#include "Wall.h"
#include "Fabric.h"
#include <iostream>
#include "Statistic.h"
#include "Cell.h"
#include <ctime>

using namespace std;

void Field::draw() {
	//char* eType;
	for(int y=0;y<Field::getHeight();y++) {
		for(int x=0;x<Field::getWidth();x++) {
			Field::elems[x][y]->draw();
			/*int typeElement = Field::elems[x][y]->getType();
			if(typeElement == 1) eType = "1";
			else if(typeElement == 2) eType = "2";
			else if(typeElement == 3) eType = "3";
			else if(typeElement == 0) eType = "0";
			else eType = "E"; // error detected
			cout << "[" << eType << "]";*/
		}
		cout << endl;
	}
}

Element* Field::getElement(int posx, int posy) {
	return Field::elems[posx][posy];
}

void Field::deleteFromMemory(int x, int y) {
	Element* elem = Field::getElement(x, y);
	delete elem;
}

void Field::update() {
	/*
	for(int i=0; i<Field::widthCells; i++) {
		for(int j=0; j<Field::heightCells; j++) {
			if(Field::counterElems[i][j] == 1) {
				Field::elems[i][j].update();
			}
		}
	}*/
	if(Field::statistic->getNumberSnakes()) Field::snake->update();
}

void Field::gameOver() {
	Field::game = false;
}

Field::Field(int width, int height, int keySize, Fabric* pFabric, Statistic* statistic)
{
	Field::statistic = statistic;

	for(int i=0; i<64; i++) {
		Field::snakeKeys[i] = 0;
	}

	Field::debug = 0;
	Field::debugCounter = 0;

	Field::pause = false;

	Field::keyCounter = 0;

	Field::game = true;

	Field::selfLink = this;

	Field::lastx = 0;
	Field::lasty = 0;

	Field::widthPixels = width;
	Field::heightPixels = height;
	Field::sizeOfKey = keySize;
	Field::widthCells = width/keySize;
	Field::heightCells = height/keySize;

	Field::elems = new Element**[Field::widthCells];

	Field::fabric = pFabric;

	for(int i=0; i<Field::widthCells; i++) {
		Field::elems[i] = new Element*[Field::heightCells];
		for(int j=0; j<Field::heightCells; j++) {
			Field::elems[i][j] = fabric->createBlank();
		}
	}

	//int snakesCount = Field::snakesCount();

/*
	for(int i=0;i<Field::widthCells;i++) {
		for(int j=0; j<Field::heightCells; j++) {
			if(Field::counterElems[i][j] == 0) {
				continue;
			} else {
				if((Field::elems[i][j]).type == 1) cout << "Food!" << endl;
				else if((Field::elems[i][j]).type == 2) cout << "Snake!" << endl;
				else if((Field::elems[i][j]).type == 3) cout << "Wall!" << endl;
			}
		}	
	}
*/

	//Field::draw();
}

bool Field::addElement(Element* elem, int posx, int posy, bool allowReplace) {	
	Field::keyCount(elem);
	
	int setx;
	int sety;

	if(Field::lasty==Field::getHeight()) {
		Field::lasty = -1;
		Field::lastx += 1;
	}
	if(posx!=-1&&posy!=-1) {
		if(posx<Field::getWidth()&&posy<Field::getHeight()&&posx>=0&&posy>=0) {
			if(Field::elems[posx][posy]->getType() == 0) {
				if(!allowReplace) return false;
			}
			setx = posx;
			sety = posy;
		} else {
			Field::setPause();
			cout << endl << "ERROR: illegal posx/posy" << endl;
			return false;
		}
	} else {
		setx = Field::lastx;
		sety = Field::lasty;
		Field::lastx++;
	}

	Field::elems[setx][sety] = elem;
}

void Field::addSnake(Snake* snake) {
	Field::snake = snake;
	for(int i=0; i<Snake::startSize; i++) {
		Field::addElement(Field::fabric->createSnakeElement(snake));
	}
}

void Field::snakeUpgrade(Snake* snake, int x, int y) {
	Field::addElement(Field::fabric->createSnakeElement(snake), x, y, true);
	Field::fabric->getStatistic()->upgradeUserScore();
}

Cell Field::getPosByKey(int key) {
	for(int i=0; i<Field::getWidth(); i++) {
		for(int j=0; j<Field::getHeight(); j++) {
			if(Field::elems[i][j]->getType() != 0) {
				if((Field::elems[i][j])->getKey() == key) {
					Cell cell;
					cell.setCoords(i, j);
					return cell;
				}
			}
		}
	}
	return false;
}

int Field::getWidth() {
	return Field::widthCells;
}

int Field::getHeight() {
	return Field::heightCells;
}

bool Field::isElem(int x, int y) {
	return Field::elems[x][y]->getType() ? true : false;
}

void Field::keyCount(Element* elem) {
	Field::keyCounter++;
	int count = Field::keyCounter;
	elem->setKey(count);
	if(elem->getType() == 2) {
		Field::snakeKeys[Field::snake->countElems()] = count;
	}
}

/*
Field* Field::getLink() {
	return Field::selfLink;
}
*/

int Field::snakesCount() {
	return 1;
}

void Field::swap(int x1, int y1, int x2, int y2) {
	if(x1<=Field::getWidth()&&x2<=Field::getWidth()&&y1<=Field::getHeight()&&y2<=Field::getHeight()) {
		Element* e1 = Field::elems[x1][y1];
		Element* e2 = Field::elems[x2][y2];
		Field::elems[x1][y1] = e2;
		Field::elems[x2][y2] = e1;
	} else {
		cout << "ERROR#2!" << endl;
	}
}

void Field::changePos(int x1, int y1, int x2, int y2) {
	if(x1<=Field::getWidth()&&x2<=Field::getWidth()&&y1<=Field::getHeight()&&y2<=Field::getHeight()) {
		Element* el = Field::elems[x1][y1];
		Element* clear = new Element();
		Field::elems[x1][y1] = clear;
		Field::elems[x2][y2] = el;
	} else {
		cout << "ERROR#3!" << endl;
	}
}

void Field::snakeEat(Snake* snake, int x, int y) {
	Field::deleteFromMemory(x, y);
	Field::newFood();
}

Cell Field::getSnakeTail() {
	int maxKey = 0;
	for(int x=0; x<Field::getWidth(); x++) {
		for(int y=0; y<Field::getHeight(); y++) {
			Element* elem = Field::getElement(x, y);
			if(elem->getType() == 2) {
				int currentKey = elem->getKey();
				if(currentKey > maxKey) maxKey = currentKey;
			}
		}
	}
	Cell lastElement = Field::getPosByKey(maxKey);
	return lastElement;
}

void Field::newFood() {
	int width = Field::getWidth();
	int height = Field::getHeight();
	int size = width*height;
	Cell freeCells[100]; // size
	int numberFreeCells=0;
	for(int x=0; x<height; x++) {
		for(int y=0; y<width; y++) {
			Element* elem = Field::getElement(x, y);
			if(elem->getType() == 0) {
				Cell cell;
				cell.setCoords(x, y);
				freeCells[numberFreeCells] = cell;
				numberFreeCells++;
			}
		}
	}
	srand(time(0));
	int numberFreeCell = rand()%numberFreeCells;
	Cell cell = freeCells[numberFreeCell];
	int cellX = cell.getX();
	int cellY = cell.getY();
	Element* elem = Field::getElement(cellX, cellY);
	Field::addElement(Field::fabric->createFood(), cellX, cellY);
}


Field* Field::selfLink;
Field* Field::getLink() {
	return Field::selfLink;
}

void Field::setPause() {
	Field::pause = true;
}
void Field::continueGame() {
	Field::pause = false;
}
bool Field::isGame() {
	return Field::game;
}
bool Field::isPause() {
	return Field::pause;
}
int Field::getDebug() {
	return Field::debug;
}
int Field::getDebugCounter() {
	return Field::debugCounter;
}
int Field::getSnakeKey(int number) {
	return Field::snakeKeys[number];
}
void Field::debugCounterUpdate() {
	Field::debugCounter++;
}

int Field::getElementType(int x, int y) {
	return Field::elems[x][y]->getType();
}

Snake* Field::getSnake() {
	return Field::snake;
}

Field::~Field(void)
{
}