#pragma once
#include "Element.h"
#include "Statistic.h"
#include "Snake.h"
#include "Fabric.h"
#include "Cell.h"

class Field
{
public:
	Field(int widht, int height, int keySize, Fabric* pFabric, Statistic* statistic);
	~Field(void);
	void draw();
	void update();
	bool addElement(Element* elem, int posx=-1, int posy=-1, bool allowReplace=true);
	void addSnake(Snake* snake);
	int getWidth();
	int getHeight();
	Element* getElement(int x,int y);
	bool isElem(int x, int y);
	void deleteFromMemory(int x, int y);
	Cell getPosByKey(int key);
	void swap(int x1, int y1, int x2, int y2);
	void changePos(int x1, int y1, int x2, int y2);
	void snakeEat(Snake* snake, int x, int y);
	void newFood();
	void gameOver();
	void snakeUpgrade(Snake* snake, int x, int y);
	bool isGame();
	bool isPause();
	void setPause();
	void continueGame();
	int getDebug();
	int getDebugCounter();
	int getSnakeKey(int number);
	void debugCounterUpdate();
	int getElementType(int x, int y);
	Cell getSnakeTail();
	Snake* getSnake();
	Statistic* statistic;
	
	static Field* selfLink;
	static Field* getLink();
private:

	Element*** elems;
	Snake* snake;

	int widthCells;
	int heightCells;
	bool game;
	bool pause;
	int debug;
	int debugCounter;
	int snakeKeys[64];

	// ---

	Fabric* fabric;
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