#include "StdAfx.h"
#include "Statistic.h"
#include <iostream>

void Statistic::setNumberSnakes(int numberSnakes) {
	Statistic::numberSnakes = numberSnakes;
}

int Statistic::getNumberSnakes() {
	int numberSnakes = Statistic::numberSnakes;
	return numberSnakes;
}

Statistic::Statistic(void)
{
	Statistic::numberSnakes = 0;
	Statistic::userScore = 0;
}

Statistic::~Statistic(void)
{
}

int Statistic::getUserScore() {
	return Statistic::userScore;
}

void Statistic::upgradeUserScore(int upgradeScore) {
	Statistic::userScore += upgradeScore;
}