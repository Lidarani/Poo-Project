#ifndef PLAYER_H
#define PLAYER_H

#include<Card.h>
#include<rlutil/rlutil.h>

class Player
{

public:
	int cards, sum;
	Card hand[16];
	bool ace;

	Player();

	int getSum();

	virtual void clearHand() = 0;

	void drawCard(int card); //Based on deck from Round

};

#endif