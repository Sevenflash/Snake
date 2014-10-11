#include "StdAfx.h"
#include "Statistic.h"
#include <iostream>

void Statistic::setNumberSnakes(int numberSnakes) {
	Statistic::numberSnakes = numberSnakes;
}

int Statistic::getNumberSnakes() {
	return Statistic::numberSnakes;
}

Statistic::Statistic(void)
{
	Statistic::numberSnakes = 0;
}

Statistic::~Statistic(void)
{
}