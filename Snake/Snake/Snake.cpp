#include "StdAfx.h"
#include "Snake.h"
#include "Statistic.h"
#include "SnakeElement.h"
#include "Field.h"

bool Snake::snakeElements() {
	//Field::snakeElements(this);
	return true;
}

bool Snake::isElements() {
	Field* field = Field::selfLink;
	bool flag = false;
	for(int i=0; i<field->getWidth(); i++) {
		for(int j=0; j<field->getHeight(); j++) {
			if(field->counterElems[i][j] == 1) {
				if((field->elems[i][j]).type == 2) return true;
			}
		}
	}
	return false;
}

void Snake::setID(int number) {
	Snake::snakeID = number;
}

SnakeElement* Snake::createHead() {
//	Snake::elems[
	return new SnakeElement();
}

SnakeElement* Snake::createBody() {
	return new SnakeElement();
}

SnakeElement* Snake::getLastElement() {
	return new SnakeElement();
}

int Snake::getID() {
	return Snake::snakeID;
}

Snake::Snake(void) {
	//this.numberSnake = Statistic::getNumberSnakes() + 1;
	std::cout << "Snake constructor" << std::endl;
	Snake::posx = 0;
	Snake::posy = 0;
	Snake::direction = 1;
};

Snake::~Snake(void){
	std::cout << "Snake destructor" << std::endl;
}

void Snake::draw() {

}

Element* Snake::getHead() {
	Field* field = Field::selfLink;
	for(int i=0; i<field->getWidth(); i++) {
		for(int j=0; j<field->getHeight(); j++) {
			if(field->isElem(i,j)) {
				Element* elem = field->getElement(i,j);
				if(elem->type == 2) {
					if(elem->snakeElementType == 1) {
						return elem;
					}
				}
			}
		}
	}
	return false;
}

void Snake::swap(int x1, int y1, int x2, int y2) {
/*
	SnakeElement* e1 = Field::elems[x1][y1];
	SnakeElement* e2 = Field::elems[x2][y2];
	Field::elems[x2][y2] = *e1;
	Field::elems[x1][y1] = *e2;
*/
}

/*
int* Snake::getElemPos(SnakeElement* snElem) {
	for(int i=0; i<Field::widthKeys; i++) {
		for(int j=0; j<Field::heightKeys; j++) {
			if(Field::counterElems[i][j] == 1) {
				if(Field::elems[i][j].type == 2) {
					int x = i;
					int y = j;
					int pos[2] = {i, j};
				}
			}
		}
	}
}
*/

Element* Snake::getElems() {
	Field* field = Field::selfLink;
	int size = Snake::countElems();
	Element* eArray;
	eArray = new Element[size];
	for(int i=0; i<field->getWidth(); i++) {
		for(int j=0; j<field->getHeight(); j++) {
			if(field->counterElems[i][j] == 1) {
				if((Snake::elems[i][j]).type == 2) {
					eArray[(i+1)*(j+1)] = Snake::elems[i][j];
				}
			}
		}
	}
	return eArray;
}

int Snake::countElems() {
	Field* field = Field::selfLink;
	int count = 0;
	for(int i=0; i<field->getWidth(); i++) {
		for(int j=0; j<field->getHeight(); j++) {
			if(field->counterElems[i][j] == 1) {
				if((Snake::elems[i][j]).type == 2) {
					count++;	
				}
			}
		}
	}
	return count;
}

void Snake::update() {
	Field* field = Field::selfLink;
	Element* head = Snake::getHead();
	if(head == false) {
		std::cout << "ERROR!" << std::endl;
	}
	int height = field->getHeight();
	int width = field->getWidth();
	int* pos = field->getPosByKey(head->key);
	int nextx=pos[0];
	int nexty=pos[1];
	if(direction==1) {
		nexty++;
		if(nexty==height) nexty=0;
	} else if(Snake::direction==2) {
		nextx++;
		if(nextx=width) nextx=0;
	} else if(Snake::direction==3) {
		nexty--;
		if(nexty=-1) nexty=height;
	} else if(Snake::direction==4) {
		nextx--;
		if(nextx==-1) nextx = width;
	}

	/*
	for(int i=0; i<Field::widthKeys; i++) {
		for(int j=0; j<Field::heightKeys; j++) {
			if(Field::counterElems[i][j] == 1) {
				if(Field::elems[i][j].type == 2) {
					for(int k=0; k<Snake::lastNumber; k++) {
						SnakeElement snElem = getByNumber(0);
						if(snElem == Field::elems[i][j]) {
							Field::elems[i][j] = Field::elems[getByNumber(k
							break;
						}
					}
				}
			}
		}
	}
	*/
}