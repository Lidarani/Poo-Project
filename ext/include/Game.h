#ifndef GAME_H
#define GAME_H

#include<Round.h>

class Game
{
	int bet = 100;
	Dealer dealer;
	Human human;

public:

	int readBet();

	void setBet(int x);

	Game();
};

#endif