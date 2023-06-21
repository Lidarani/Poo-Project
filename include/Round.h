#ifndef ROUND_H
#define ROUND_H

#include<vector>
#include<memory>
#include<Dealer.h>
#include<Human.h>

class Round
{
	bool turn, done;// done = 1 -> dealer is
	// not bust but has over 16, or a player
	// has blackjack or is bust;
	// turn = 0 - Human turn, 1 - Dealer turn

	std::vector<int> deck;
	// value: A - 1, 2 - 2, ...,   J - 11 Q - 12, K - 13;
	// first card(1) is A ♥ -  0 * 13 + 1, 0 - ♥, 1 - A;
	// last card(52) K ♠ - 3 * 13 + 13;
	// deck[3] = 14 -> 4th Card is A ♦ (1 * 13 + 1)

	std::unique_ptr<Dealer> dealer = std::make_unique<Dealer>();
	std::unique_ptr<Human> human = std::make_unique<Human>();

	void shuffleDeck();

public:
	Round();

	int getHMoney(); // return money amount of human

	int getCard(); // get a card from deck (1 - 52)

	void resetRound(); // reset Round

	bool dealerTurn(); // returns turn bool

	bool isDone(); //return done bool

	bool brokeHuman(); //checks if human money == 0

	void outCards(); // cout cards

	bool hasBlackjack(Player* currentPlayer);
	// checks and displays if player has Blackjack

	bool isBusted(Player* currentPlayer);
	// checks and displays if player is bust

	void Turn(Player* currentPlayer);
	// actions of player or dealer in a turn
	// player starts, each turn either hits or stands. 
	// when he stands, it s now the dealer to play
	// each dealer turn he hits
	// until last turn, when he has more than 16
	// he s either bust or he stands

	void playRound(const int bet);
	//the entire round
};

#endif