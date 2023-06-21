#ifndef DEALER_H
#define DEALER_H

#include<Player.h>

class Dealer : public Player 
{
	bool hiddenCard;

public:

	Dealer();

	Dealer(const Dealer& other);
	
	void openCard();

	void clearHand();

	friend std::wostream& operator<<(std::wostream & wos, Dealer &D);

};

#endif