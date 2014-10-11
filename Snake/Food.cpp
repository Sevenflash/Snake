#include "StdAfx.h"
#include "Food.h"
#include <iostream>

Food::Food(void)
{
	Food::setType(1);
}

Food::~Food(void)
{
}

void Food::draw() {
	std::cout << "[1]";
}

void Food::update() {

}