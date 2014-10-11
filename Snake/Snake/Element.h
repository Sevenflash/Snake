#pragma once

class Element
{
public:
	Element(void);
	~Element(void);
	int type;
	void draw();
	void update();
	int posx;
	int posy;
	int key;
	/* Snake */
	int snakeElementType;
	bool last;
};