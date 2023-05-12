#include <Card.h>
#include <rlutil.h>

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
		ace = false;
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