#include "StdAfx.h"
#include "Snake.h"
#include "Statistic.h"
#include "SnakeElement.h"
#include "Field.h"

using namespace std;



bool Snake::snakeElements() {
	//Field::snakeElements(this);
	return true;
}

bool Snake::isElements() {
	Field* field = Field::getLink();
	bool flag = false;
	for(int i=0; i<field->getWidth(); i++) {
		for(int j=0; j<field->getHeight(); j++) {
			if(field->getElementType(i, j) == 2) return true;
		}
	}
	return false;
}

void Snake::setID(int number) {
	Snake::snakeID = number;
}

int Snake::getID() {
	return Snake::snakeID;
}

Snake::Snake(void) {
	//this.numberSnake = Statistic::getNumberSnakes() + 1;
	//std::cout << "Snake constructor" << std::endl;
	Snake::posx = 0;
	Snake::posy = 0;
	Snake::direction = 4;
};

Snake::~Snake(void){
	//std::cout << "Snake destructor" << std::endl;
}

void Snake::draw() {

}

Element* Snake::getHead() {
	Field* field = Field::getLink();
	for(int i=0; i<field->getWidth(); i++) {
		for(int j=0; j<field->getHeight(); j++) {
			if(field->isElem(i,j)) {
				Element* elem = field->getElement(i,j);
				if(elem->getType() == 2) {
					if(elem->isHead()) {
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
	for(int i=0; i<Field::widthCells; i++) {
		for(int j=0; j<Field::heightCells; j++) {
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
	Field* field = Field::getLink();
	int size = Snake::countElems();
	Element* eArray;
	eArray = new Element[size];
	for(int i=0; i<field->getWidth(); i++) {
		for(int j=0; j<field->getHeight(); j++) {
			if((Snake::elems[i][j]).getType() == 2) {
				eArray[(i+1)*(j+1)] = Snake::elems[i][j];
			}
		}
	}
	return eArray;
}

bool Snake::directionChanged() {
	return Snake::flagDirectionChanged;
}

int Snake::countElems() {
	Field* field = Field::getLink();
	int count = 0;
	for(int i=0; i<field->getWidth(); i++) {
		for(int j=0; j<field->getHeight(); j++) {
			if(field->getElementType(i, j) == 2) {
				count++;	
			}
		}
	}
	return count;
}

void Snake::changeDirection(int d) {
	int eatSelf = (d-2)>0 ? d-2 : 2+d;
	if(eatSelf == Snake::direction) return;
	Snake::direction = d;
	Snake::flagDirectionChanged = true;
}

void Snake::update() {
	Snake::flagDirectionChanged = false;
	bool triggerUpdate = false;
	int nextx = 0;
	int nexty = 0;
	Field* field = Field::getLink();
	Element* head = Snake::getHead();
	
	Cell lastElement = field->getSnakeTail();
	
	int sKey = head->getKey();

	if(head == false) {
		std::cout << "ERROR!" << std::endl;
	}
	int height = field->getHeight();
	int width = field->getWidth();
	Cell cell = field->getPosByKey(sKey);
	int posx = cell.getX();
	int posy = cell.getY();
	nextx=posx;
	nexty=posy;
	if(Snake::direction==1) {
		nexty--;
		if(nexty==-1) nexty=height-1;
	} else if(Snake::direction==2) {
		nextx++;
		if(nextx==width) nextx=0;
	} else if(Snake::direction==3) {
		nexty++;
		if(nexty==height) nexty=0;
	} else if(Snake::direction==4) {
		nextx--;
		if(nextx==-1) nextx = width-1;
	}
	if(field->isElem(nextx, nexty)) {
		Element* elem = field->getElement(nextx, nexty);
		if(elem->getType() == 1) { // food
			field->snakeEat(this, nextx, nexty);
			triggerUpdate = true;
		} else if(elem->getType() == 3 || elem->getType() == 2) {
			field->gameOver();
		}
	}
	field->changePos(posx, posy, nextx, nexty);
	int previousX=0;
	int previousY=0;
	for(int i=1; i<Snake::countElems(); i++) {
		Cell cell = field->getPosByKey(field->getSnakeKey(i));
		int x = cell.getX();
		int y = cell.getY();
		if(i==1) {
			//cout << x << y << "|" << posx << posy << endl;
			field->changePos(x, y, posx, posy);
		} else {
			field->changePos(x, y, previousX, previousY);
		}
		previousX = x;
		previousY = y;
	}
	if(triggerUpdate) 
		field->snakeUpgrade(this, lastElement.getX(), lastElement.getY());
	/*
	for(int i=0; i<Field::widthCells; i++) {
		for(int j=0; j<Field::heightCells; j++) {
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