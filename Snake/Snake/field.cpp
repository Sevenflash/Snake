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

using namespace std;

Field* Field::selfLink;

/*
bool Field::snakeElements(Snake* snake) {
	bool isElem=false;
	for(int i=0; i<this.widthKeys; i++) {
		for(int j=0; j<this.heightKeys; j++) {
			if((*snake).elems[i][j].type != 0) {
				isElem = true;
			}
		}
	}
	return isElem;
}
*/
Element** eachElement(char fnName[20]) {
/*	void(*fPointer)(Element* elem);
	fPointer = &fnName;
	for(int i=0; i<Field::widthKeys; i++) {
		for(int j=0; j<Field::heightKeys; j++) {
			fPointer(&(Field::elems[i][j]));
		}
	} */
	Element** a = new Element*[1];
	return a;
}

void Field::draw() {
	char* eType;
	for(int i=0;i<Field::widthKeys;i++) {
		for(int j=0;j<Field::heightKeys;j++) {
			if(Field::counterElems[i][j] == 1) {
				if((Field::elems[i][j]).type == 1) eType = "1";
				else if((Field::elems[i][j]).type == 2) eType = "2";
				else if((Field::elems[i][j]).type == 3) eType = "3";
			} else {
				eType = "0";
			}
			cout << "[" << eType << "]"; // (Field::widthKeys*(i+1)+j+1)-Field::widthKeys
		}
		cout << endl;
	}
	//Field::snake->draw();
}

Element* Field::getElement(int posx, int posy) {
	return &(Field::elems[posx][posy]);
}

void Field::update() {
	/*
	for(int i=0; i<Field::widthKeys; i++) {
		for(int j=0; j<Field::heightKeys; j++) {
			if(Field::counterElems[i][j] == 1) {
				Field::elems[i][j].update();
			}
		}
	}*/
	Field::snake->update();
}

Field::Field(int width, int height, int keySize, Fabric* pFabric)
{
	Field::selfLink = this;

	Field::lastx = 0;
	Field::lasty = 0;

	Field::widthPixels = width;
	Field::heightPixels = height;
	Field::sizeOfKey = keySize;
	Field::widthKeys = width/keySize;
	Field::heightKeys = height/keySize;

	Field::elems = new Element*[Field::widthKeys];

	Field::counterElems = new int*[Field::widthKeys];

	Field::fabric = pFabric;

	for(int i=0; i<Field::widthKeys; i++) {
		Field::elems[i] = new Element[Field::heightKeys];
		Field::counterElems[i] = new int[Field::heightKeys];
		for(int j=0; j<Field::heightKeys; j++) {
			Element* pe = new Element();
			Element oe = *pe;
			Field::elems[i][j] = oe;
			Field::counterElems[i][j] = 0;
		}
	}

	//int snakesCount = Field::snakesCount();

/*
	for(int i=0;i<Field::widthKeys;i++) {
		for(int j=0; j<Field::heightKeys; j++) {
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

void Field::addElement(Element elem, int posx, int posy) {
	Field::keyCount(&elem);
	
	int setx;
	int sety;

	if(Field::lasty==Field::heightKeys) {
		Field::lasty = -1;
		Field::lastx += 1;
	}
	if(posx!=-1&&posx!=-1) {
		if(posx<=Field::widthKeys&&posy<=Field::heightKeys) {
			if(Field::counterElems[posx][posy] = 0) {
				Field::lasty++;
				setx = posx;
				sety = posy;
			}
		}
	} else {
		setx = Field::lastx;
		sety = Field::lasty;
	}

	Field::lasty++;
	Field::elems[setx][sety] = elem;
	Field::counterElems[setx][sety] = 1;
	cout << setx << "|" << sety;
	cout << endl;
}

void Field::addSnake(Snake* snake) {
	Field::snake = snake;
	Snake oSnake = *snake;
	for(int i=0; i<Snake::startSize; i++) {
		Field::addElement(Field::fabric->createSnakeElement(snake));
	}
}

int* Field::getPosByKey(int key) {
	for(int i=0; i<Field::widthKeys; i++) {
		for(int j=0; j<Field::heightKeys; j++) {
			if(Field::counterElems[i][j] == 1) {
				if(Field::elems[i][j].key == key) {
					int pos[2];
					pos[0] = i;
					pos[1] = j;
					int* ppos = pos;
					return ppos;
				}
			}
		}
	}
	return false;
}

int Field::getWidth() {
	return Field::widthKeys;
}

int Field::getHeight() {
	return Field::heightKeys;
}

bool Field::isElem(int x, int y) {
	return Field::counterElems[x][y] ? true : false;
}

void Field::keyCount(Element* elem) {
	(Field::keyCounter)++;
	int count = Field::keyCounter;
	elem->key = count;
}

/*
Field* Field::getLink() {
	return Field::selfLink;
}
*/

int Field::snakesCount() {
	return 1;
}

Field::~Field(void)
{
}