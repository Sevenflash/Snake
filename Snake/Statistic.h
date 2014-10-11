#pragma once

class Statistic
{
private:
	int numberSnakes;
	int numberElements;
	int userScore;
public:
	Statistic(void);
	~Statistic(void);
	void setNumberSnakes(int numberSnakes);
	int getNumberSnakes();
	int getNumberElements();
	int getUserScore();
	void upgradeUserScore(int upScore=1);
};