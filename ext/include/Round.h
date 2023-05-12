#include<vector>
#include<Player.h>

class Round
{
	std::vector<int> deck;
	// value: A -> 1, 2 -> 2, ...,   J -> 11 Q -> 12, K -> 13; !!! Blank card for dealer - 0 suite 0 value
	//first card(1) is A ♥ -  0 * 13 + 1, 0 - ♥, 1 - A;  last card(52) K ♠ - 3 * 13 + 13;
	//deck[3] = 14 -> 4th Card is A ♦ (1 * 13 + 1)

	void shuffleDeck()
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

public:
	int getCard()
	{
		int x = deck.back();
		deck.pop_back();
		return x;
	}

	Round()
	{
		shuffleDeck();
	}

	Round(Player& dealer, Player& human, int bet)
	{
		human.clearHand();
		dealer.clearHand();

		shuffleDeck();

		dealer.drawCard(getCard());
		human.drawCard(getCard());

		dealer.drawCard(getCard());
		human.drawCard(getCard());
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
				dealer.setMoney(human.getMoney() - bet * 3 / 2);

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
						dealer.setMoney(human.getMoney() - bet);
					}

					else if (dealer.getSum() > human.getSum())
					{
						std::cout << "You lose!\n";
						human.setMoney(human.getMoney() - bet);
						dealer.setMoney(human.getMoney() + bet);
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
};