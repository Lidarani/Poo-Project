#include<Round.h>

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
	deck.push_back(0);
}

void Round::initRound(Dealer& dealer, Human& human)
{
	human.clearHand();
	dealer.clearHand();

	shuffleDeck();

	dealer.drawCard(getCard());
	human.drawCard(getCard());

	dealer.drawCard(getCard());
	human.drawCard(getCard());
}

int Round::getCard()
{
	int x = deck.back();
	deck.pop_back();
	return x;
}

Round::Round()
{
	shuffleDeck();
}

Round::Round(Dealer &dealer, Human &human, int bet)
{
	initRound(dealer, human);

	bool drawn = false;
	int attempts = 0;

	while (true)
	{
		rlutil::cls();
		std::cout << "Dealer: " << dealer << '\n' << "Player: " << human;

		if (human.getSum() > 21)
		{
			std::cout << "\nYou lost " << bet << "\n\n";
			human.setMoney(human.getMoney() - bet);

			rlutil::msleep(3000);
			break;
		}

		if (human.getSum() == 21 && !drawn)
		{
			std::cout << "\nBLACKJACK!\n";
			human.setMoney(human.getMoney() + bet * 3 / 2);

			rlutil::msleep(3000);
			break;
		}

		else
		{
			char d = '-';
			std::cout << "\n(h)it or (s)tand\n";
			std::cin >> d;

			if (attempts == 10)
				d = 's';

			if (d == 'h')
			{
				human.drawCard(getCard());
				drawn = true;
			}

			else if ( d == 's')
			{
				dealer.openCard(getCard());

				while (dealer.getSum() < 17)
					dealer.drawCard(getCard());

				rlutil::cls();
				std::cout << "Dealer: " << dealer << '\n' << "Player: " << human << '\n';

				int dealerSum = dealer.getSum(), humanSum = human.getSum();

				if (dealerSum > 21 || dealerSum < humanSum)
				{
					std::cout << "You Win!\n";
					human.setMoney(human.getMoney() + bet);
				}

				else if (dealer.getSum() > human.getSum())
				{
					std::cout << "You lose!\n";
					human.setMoney(human.getMoney() - bet);
				}

				else
				{
					std::cout << "Push! It is a tie! \n";
				}

				rlutil::msleep(3000);
				break;
			}
			else
				attempts++;
		}
	}
}