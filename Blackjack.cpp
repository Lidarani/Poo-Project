#include<iostream>
#include<cstdlib>
#include<ctime>
#include<random>
#include<string>
#include<vector>
#include<cstring>
#include<fstream>
#include<thread>
#include<chrono>
#include <Rlutil.h>

std::ofstream fout("debug.txt");

//std::string suites[] = {"\u2661", "\u2662", "\u2667", "\u2664"}; // for cout, suite: ♥ - 0, ♦ - 1, ♣ - 2, ♠ - 3;

void printVector(std::vector<int> v)
{
	int n = v.size();
	fout << n << '\n';
	for (int i = 0; i < n; i++)
		fout << v[i] << ' ';
	fout << '\n';
}

class Card
{
	int suite, value;

public:
	Card()
	{
		suite = 0;
		value = 0;
	}

	explicit Card(const int card)
	{
		suite = card / 13;
		if (suite > 3)
			suite = 3;
		value = card == 0 ? 0 : card % 13 + 1;
	}

	Card(const Card& c)
	{
		suite = c.suite;
		value = c.value;
	}

	Card operator=(const Card& c)
	{
		if(this == &c)
		{
			return *this;
		}
		suite = c.suite;
		value = c.value;
		return *this;
	}

	char getValue()
	{
		if (value == 0)
			return '0';
		if (value == 1)
			return 'A';
		if (value < 10)
			return value + '0';
		if (value == 10)
			return '~';
		if (value == 11)
			return 'J';
		return value == 12 ? 'Q' : 'K';
	}

	int getSuite() {return suite;}

	void setValue(int v) {value = v;}

	void setSuite(int s) {suite = s;}

	friend std::ostream& operator<<(std::ostream& os, const Card& c)
	{
		std::cout << c.suite << ' ' << c.value << '\n';
		return os;
	}
};

class Player
{
	int money, cards = 0, sum = 0;
	Card hand[16];
	bool ace = false;

public:

	Player()
	{
		money = 0;
		cards = 0;
	}

	int getMoney() {return money;}

	void setMoney(int x) {money = x;}

	int getSum() {return sum;}

	void clearHand()
	{
		cards = 0;
		sum = 0;
	}

	friend std::ostream& operator<<(std::ostream& os, Player& p)
	{
		if (p.hand[0].getValue() == '0')
			std::cout << "???\n";

		else if (p.sum > 21)
		{
			std::cout << "Busted!\n";
		}
		else
			std::cout << p.sum << '\n';

		for (int i = 0; i < p.cards; i++)
			std::cout << " ___  ";

		std::cout << '\n';

		for (int i = 0; i < p.cards; i++)
		{
			char v;
			v = p.hand[i].getValue();
			if (v == '0')
				std::cout << "|###| ";
			else if (v == '~')
				std::cout << "|10 | ";
			else
				std::cout << "|" << v << "  | ";
		}

		std::cout << '\n';


		for (int i = 0; i < p.cards; i++)
		{
			char v = p.hand[i].getValue();
			if (v == '0')
				std::cout << "|###| ";
			else
			{
				char s = p.hand[i].getSuite() + 3;
				std::cout << "| " << s << " | ";
			}
		}

		std::cout << '\n';

		for (int i = 0; i < p.cards; i++)
		{
			char v;
			v = p.hand[i].getValue();
			if (v == '0')
				std::cout << "|###| ";
			else if (v == '~')
				std::cout << "|_10| ";
			else
				std::cout << "|__" << v << "| ";
		}

		std::cout << '\n';

		return os;
	}


	void openCard(int card) //replace the blank dealer card
	{
		Card D(card);
		hand[0] = D;

		int v = card % 13 + 1;
		if (v == 1)
		{
			ace = true;
			if (sum <= 10)
				sum += 11;
			else sum++;
		}
		else if (v <= 10)
			sum += v;
		else
			sum += 10;

		if (sum > 21 && ace)
		{
			ace = false;
			sum -= 10;
		}
	}

	void drawCard(int card) //Based on deck from Round
	{
		int s = card / 13;
		int v = card == 0 ? 0 : card % 13 + 1;
		if (card == 52)
		{
			s = 0;
			v = 1;
		}
		hand[cards].setSuite(s);
		hand[cards].setValue(v);
		cards++;

		if (!v);
		else if (v == 1)
		{
			ace = true;
			if (sum <= 10)
				sum += 11;
			else sum++;
		}
		else if (v <= 10)
			sum += v;
		else
			sum += 10;

		if (sum > 21 && ace)
		{
			ace = false;
			sum -= 10;
		}
	}

};

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

		srand(time(0));
		for (; n > 0; n--)
		{
			int aux = rand() % n;
			deck.push_back(num[aux]);
			std::swap(num[aux], num[n - 1]);
			num.pop_back();
		}
		deck.push_back(0);
		printVector(deck);
	}

public:
	int getCard()
	{
		int x = deck.back();
		fout << x << '\n';
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

		fout << "dealer ";
		dealer.drawCard(getCard());
		fout << "human ";
		human.drawCard(getCard());

		fout << "dealer ";
		dealer.drawCard(getCard());
		fout << "human ";
		human.drawCard(getCard());
		bool drawn = false;

		while (true)
		{
			rlutil::cls();
			std::cout << "Dealer: " << dealer << '\n' << "Player: " << human;
			char d;

			if (human.getSum() > 21)
			{
				std::cout << "\nYou lost " << bet << "\n\n";
				human.setMoney(human.getMoney() - bet);

				std::cin >> d; //getch any char to continue
				break;
			}

			if (human.getSum() == 21 && !drawn)
			{
				std::cout << "\nBLACKJACK!\n";
				human.setMoney(human.getMoney() + bet * 3 / 2);
				dealer.setMoney(human.getMoney() - bet * 3 / 2);
				break;
			}

			else
			{
				std::cout << "\n(h)it or (s)tand\n";
				std::cin >> d;

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

					break;
				}
			}
		}
	}
};

class Game
{
	int bet = 100;
	Player dealer, human;

public:

	int getBet()
	{
		bet = 0;
		char s[100];

		std::cin >> s;

		int len = strlen(s);
		for (int i = 0; i < len; i++)
			if (!isdigit(s[i]))
				return -1;
			else
				bet = bet * 10 + s[i] - '0';

		if (bet <= human.getMoney())
			return 1;

		bet = 0;
		return 0;

	}

	Game()
	{
		human.setMoney(5000);
		dealer.setMoney(1000000);
		int cond = 2, retry = 1;

		rlutil::cls();
		while (retry)
			while (true)
			{
				if (human.getMoney() == 0)
				{
					while (true)
					{
						rlutil::cls();
						std::cout << "You lost all your money! Want to try again? y/n";
						char x;
						std::cin >> x;
						if (x == 'n')
						{
							retry = 0;
							break;
						}
						if (x == 'y')
							break;
					}
				}

				rlutil::cls();

				std::cout << " Rules: \n Try to get as close to 21 without going over. \n Kings, Queens, and Jacks are worth 10 points. \n Aces are worth 1 or 11 points. \n Cards 2 through 10 are worth their face value \n (H)it to take another card. \n (S)tand to stop taking cards \n In case of a tie, the bet is returned to the player. \n The dealer stops hitting at 17.\n\n Money: " << human.getMoney() << "\n\n";

				if (cond == -1)
					std::cout << " Please provide a valid number!\n";
				else if (cond == 0)
					std::cout << " Not enough money!\n";

				std::cout << " How much do you bet?\n Bet:";

				if (cond == 1)
					Round r(dealer, human, bet);
				
			cond = getBet();
			}
	}
};

int main()
{
	char d;
	Game g;
	while (true)
	{
		std::cin >> d;
		if (d == 'y')
			Game g2;
		if (d == 'n')
			break;
	}

	return 0;
}