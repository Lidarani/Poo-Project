#include<Round.h>

Round::Round()
{
	turn = 0;
	done = 0;

	shuffleDeck();
}

int Round::getHMoney()
{
	return human->getMoney();
}

void Round::shuffleDeck()
{
	std::vector<int> num;
	int n = 52;
	for (int i = 1; i <= 52; i++)
		num.push_back(i);

	for (; n > 0; n--)
	{
		int aux = rand() % n;
		deck.push_back(num[aux]);
		std::swap(num[aux], num[n - 1]);
		num.pop_back();
	}
}

int Round::getCard() // Next card from deck, keepin it for pop_back;
{
	int x = deck.back();
	deck.pop_back();
	return x;
}


void Round::resetRound()
{
	human->clearHand();
	dealer->clearHand();

	shuffleDeck();

	//first 2 cards of each player
	dealer->drawCard(getCard());
	human->drawCard(getCard());

	dealer->drawCard(getCard());
	human->drawCard(getCard());

	turn = 0; // human's turn now;
	done = 0; // game not done - still turns left;
}

bool Round::dealerTurn() {return turn;}

bool Round::isDone() {return done;}

bool Round::brokeHuman() {return human->getMoney() == 0;}

void Round::outCards()
{
	rlutil::cls();
	std::cout << "Dealer: " << *dealer << '\n' << "Player: " << *human;
}

bool Round::hasBlackjack(Player* currentPlayer) //If the player has Blackjack
{
	if (currentPlayer->getSum() == 21)
	{
		if (dynamic_cast<Human*>(currentPlayer))
		{
			done = 1;

			std::cout << "\n You have BLACKJACK!!\n";
			rlutil::msleep(3000);
			return true;
		}

		else if (Dealer *dealerPlayer = dynamic_cast<Dealer*>(currentPlayer))
		{
			dealerPlayer->openCard();
			outCards();

			std::cout << "\n Dealer has Blackjack! \n You lost!\n";
			rlutil::msleep(3000);
			return true;
		}
	}
	//else throw faulty dynamic cast

	return false;
}

bool Round::isBusted(Player* currentPlayer) // If the Player is bust
{

	if (currentPlayer->getSum() > 21)
	{
		if (dynamic_cast<Human*>(currentPlayer))
		{
			done = 1;
			outCards();
			std::cout << "\n You lost!\n";
			rlutil::msleep(3000);
			return true;
		}
		else if (dynamic_cast<Dealer*>(currentPlayer))
		{
			done = 1;
			outCards();
			std::cout << "\n You win! \n";
			rlutil::msleep(3000);
			return true;
		}
		//else throw exception faulty dynamic cast
	}
	return false;
}

void Round::Turn(Player* currentPlayer)
{
	outCards();

	if (Human* humanPlayer = dynamic_cast<Human*>(currentPlayer))
	{
		int attempts = 0;
		char d = '-';

		while (d != 's' && d != 'h' && attempts++ < 10)
		{
			rlutil::cls();
			outCards();

			std::cout << "\n (h)it or (s)tand \n> ";
			std::cin >> d;
		}

		if (d == 'h')
			humanPlayer -> drawCard(getCard());

		else
			turn = 1;
	}

	else if (Dealer* dealerPlayer = dynamic_cast<Dealer*>(currentPlayer))
	{
		dealerPlayer->openCard();

		if (dealerPlayer-> getSum() < 17)
			dealerPlayer-> drawCard(getCard());
		else
			done = 1;
	}
}

void Round::playRound(const int bet)
{
	outCards();

	if (hasBlackjack(human.get()))
	{
		human->addMoney(bet * 3 / 2);
		return;
	}

	if (hasBlackjack(dealer.get()))
	{
		human->subMoney(bet);
		return;
	}

	while (!dealerTurn()) // Human turn, if he s busted, round over
	{
		if (isBusted(human.get()))
		{
			human->subMoney(bet);
			return;
		}
		Turn(human.get());
	}

	while (!isDone())
	{
		if (isBusted(dealer.get()))
		{
			human->addMoney(bet);
			return;
		}
		Turn(dealer.get());
	}


//If we're here, both players are standing
// and none is Bust or has Blackjack.

	if (human->getSum() > dealer->getSum())
	{
		outCards();
		std::cout << "You win " << bet << "!\n";
		human->addMoney(bet);
		rlutil::msleep(3000);
	}

	else if (human->getSum() == dealer->getSum())
	{
		outCards();
		std::cout << "It's a tie!\n";
		rlutil::msleep(3000);
	}

	else
	{
		outCards();
		std::cout << "You lost " << bet << " ...\n";
		human->subMoney(bet);
		rlutil::msleep(3000);
	}
}