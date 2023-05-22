#ifndef ROUND_H
#define ROUND_H

#include<vector>
#include<Dealer.h>
#include<Human.h>

class Round
{
	std::vector<int> deck;
	// value: A -> 1, 2 -> 2, ...,   J -> 11 Q -> 12, K -> 13; !!! Blank card for dealer - 0 suite 0 value
	//first card(1) is A ♥ -  0 * 13 + 1, 0 - ♥, 1 - A;  last card(52) K ♠ - 3 * 13 + 13;
	//deck[3] = 14 -> 4th Card is A ♦ (1 * 13 + 1)

	void shuffleDeck();

	void initRound(Dealer& dealer, Human& human);

public:
	int getCard();

	Round();

	Round(Dealer& dealer, Human& human, int bet);

};

#endif