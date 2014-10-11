#include "StdAfx.h"
#include "Element.h"
#include <iostream>

Element::Element(void)
{
	Element::setKey(0);
	Element::setType(0);
}

Element::~Element(void)
{
}

void Element::update() {

}

void Element::draw() {
	std::cout << "[0]";
}

void Element::setType(int type) {
	Element::type = type;
}

int Element::getType() {
	return Element::type;
}

void Element::setKey(int key) {
	Element::key = key;
}

int Element::getKey() {
	return (Element::key);
}