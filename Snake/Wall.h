#pragma once
#include "Element.h"

class Wall:public Element
{
public:
	Wall(void);
	~Wall(void);

	virtual void draw();
	virtual void update();
};
