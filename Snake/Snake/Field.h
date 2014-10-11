#pragma once
#include "Element.h"
#include "Statistic.h"
#include "Snake.h"
#include "Fabric.h"

class Field
{
	//static bool Field::snakeElements(Snake* snake);
	static Element** eachElement(char fnName[20]);
public:
	Field(int widht, int height, int keySize, Fabric* pFabric);
	~Field(void);
	void draw();
	void update();
	int widthKeys;
	int heightKeys;
	void addElement(Element elem, int posx=-1, int posy=-1);
	void addSnake(Snake* snake);
	Element** elems;
	int** counterElems;
	int getWidth();
	int getHeight();
	Element* getElement(int x,int y);
	bool isElem(int x, int y);
	//static Field* getLink();
	static Field* selfLink;
	int* getPosByKey(int key);
private:
	Fabric* fabric;
	Snake* snake;
	Snake* snakes;
	int testInt[2];
	int widthPixels;
	int heightPixels;
	int sizeOfKey;
	int lastx;
	int lasty;

	int elemsCount();
	int snakesCount();
	void whileTest();

	int keyCounter;
	void keyCount(Element* elem);
};