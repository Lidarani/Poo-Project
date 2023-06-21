#ifndef PLAYER_H
#define PLAYER_H

#include<Card.h>
#include<rlutil/rlutil.h>
#include<vector>

class Player
{

protected:
	int sum;
	bool ace;
	std::vector<Card> hand;
	std::vector<std::wstring> symbols = {L"\u2660", L"\u2663", L"\u2665", L"\u2666"};

public:

	Player();

	Player(const Player& other);

	int getSum();

	std::wstring getSymbol(int suite);

	void drawCard(int card); //Based on deck from Round

	virtual void clearHand() = 0;

};

#endif