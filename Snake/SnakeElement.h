#pragma once
#include "Element.h"

class SnakeElement:public Element
{
public:
	SnakeElement(void);
	~SnakeElement(void);

	virtual void setAsHead();
	virtual bool isHead();
	
	virtual void update();
	virtual void draw();
private:
	bool headFlag;
};