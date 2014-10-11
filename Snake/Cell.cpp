#include "StdAfx.h"
#include "Cell.h"

Cell::Cell(int x, int y)
{
	Cell::x = x;
	Cell::y = y;
}

Cell::~Cell(void)
{
}

void Cell::setX(int x) {
	Cell::x = x;
}

void Cell::setY(int y) {
	Cell::y = y;
}

void Cell::setCoords(int x, int y) {
	Cell::x = x;
	Cell::y = y;
}

int Cell::getX() {
	return Cell::x;
}

int Cell::getY() {
	return Cell::y;
}