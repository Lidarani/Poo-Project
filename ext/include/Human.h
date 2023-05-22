#ifndef HUMAN_H
#define HUMAN_H

#include<Player.h>

class Human : public Player
{
	int money;

public:

	Human();

	int getMoney();

	void setMoney(const int x);

	void clearHand();

	friend std::ostream& operator<<(std::ostream & os, Human &p);
};

#endif