#ifndef DEALER_H
#define DEALER_H

#include<Player.h>

class Dealer : public Player 
{
	bool hiddenCard;

public:

	Dealer();

	void openCard(int card);

	void clearHand();

	friend std::ostream& operator<<(std::ostream & os, Dealer &D);

};

#endif