#include "StdAfx.h"
#include "SnakeElement.h"
#include <iostream>

SnakeElement::SnakeElement(void)
{
	SnakeElement::setType(2);
	SnakeElement::headFlag = false;
}

SnakeElement::~SnakeElement(void)
{
}

void SnakeElement::setAsHead() {
	SnakeElement::headFlag = true;
}

bool SnakeElement::isHead() {
	return SnakeElement::headFlag;
}

void SnakeElement::draw() {
	std::cout << "[2]";
}

void SnakeElement::update() {

}