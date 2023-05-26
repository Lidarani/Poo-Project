#ifndef HUMAN_H
#define HUMAN_H

#include<Player.h>

class Human : public Player
{
	int money;

public:

	Human();

	Human(const Human& other);

	int getMoney();

	void addMoney(const int x);

	void subMoney(const int x);

	void resetMoney();

	void clearHand();

	friend std::ostream& operator<<(std::ostream & os, Human &p);
};

#endif