#pragma once

class Statistic
{
private: // public
	//Statistic(void);
	//~Statistic(void);
	//Statistic instance;
	int numberSnakes;
	int numberElements;
public:
	Statistic(void);
	~Statistic(void);
	void setNumberSnakes(int numberSnakes);
	int getNumberSnakes();
	int getNumberElements();
	//Statistic getInstance();
};