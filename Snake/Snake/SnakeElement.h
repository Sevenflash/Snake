#pragma once
#include "Element.h"

class SnakeElement:public Element
{
public:
	SnakeElement(void);
	~SnakeElement(void);
	int snakeElementType; // 1 - head, 2 - body.
	int last;
	int number;
	int nextx;
	int nexty;
};