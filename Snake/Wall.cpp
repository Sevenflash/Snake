#include "StdAfx.h"
#include "Wall.h"
#include <iostream>

Wall::Wall(void)
{
	Wall::type = 3;
}

Wall::~Wall(void)
{
}

void Wall::draw() {
	std::cout << "[3]";
}

void Wall::update() {

}