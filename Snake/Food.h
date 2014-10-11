#pragma once
#include "Element.h"

class Food:public Element
{
public:
	Food(void);
	~Food(void);

	virtual void draw();
	virtual void update();
};
