#ifndef GAME_H
#define GAME_H

#include<Round.h>

class Game
{
	int bet = 0;
	Round r;
	
public:

	Game();

	void outRules();

	void readBet();

	void playGame();

	bool humanIsBroke();
};

#endif