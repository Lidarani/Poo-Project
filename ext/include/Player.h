#ifndef PLAYER_H
#define PLAYER_H

#include<Card.h>
#include<rlutil/rlutil.h>
#include<vector>

class Player
{

protected:
	int sum;
	std::vector<Card> hand;
	bool ace;

public:

	Player();

	Player(const Player& other);

	int getSum();

	void drawCard(int card); //Based on deck from Round

	virtual void clearHand() = 0;

};

#endif