#pragma once

class Cell
{
public:
	Cell(int x=0, int y=0);
	~Cell(void);
	int getX();
	int getY();
	void setCoords(int x, int y);
	void setX(int x);
	void setY(int y);
private:
	int x;
	int y;
};
