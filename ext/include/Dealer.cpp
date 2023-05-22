#include<Dealer.h>
#include<fstream>

Dealer::Dealer()
{
	hiddenCard = true;
}

void Dealer::openCard(int card) //replace the blank dealer car
{
	Card D(card);
	hand[0] = D;
	hiddenCard = false;

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

void Dealer::clearHand()
{
	hiddenCard = true; // Dealer only

	for(int i = 0; i < cards; i++)
		hand[i] = Card(0);
	cards = 0;
	sum = 0;
	ace = false;
}

std::ostream& operator<<(std::ostream & os, Dealer &d)
{
	// Daca avem carte ascunsa inseamnca ca dealer-ul are doar 2 carti
	// Afisam pentru prima ### si apoi pe a 2-a carte

	if (d.hiddenCard)
	{
		char v = d.hand[1].getValue(), s = d.hand[1].getSuite() + 3;
		std::string strUp = "", strDown = "";

		// formam prin v strUp - numarul de sus pentru a 2-a carte
		// si strDown - numarul de jos pentru a 2-a carte
		// formam in s simbolul pentru a 2-a carte

		if (v == '~')
			strUp = strDown = "10";

		else
		{
			strUp += v;
			strUp += ' ';

			strDown += '_';
			strDown += v;
		}
			std::cout << "???\n"
			<<" ___   ___\n"
			<<"|###| |" << strUp << " |\n"
			<<"|###| | " << s << " |\n"
			<<"|###| |_" << strDown << "|\n";
	}

	else
	{
		if (d.sum > 21)
		{
			std::cout << "Busted!\n";
		}
		else
			std::cout << d.sum << '\n';

		for (int i = 0; i < d.cards; i++)
			std::cout << " ___  ";

		std::cout << '\n';

		for (int i = 0; i < d.cards; i++)
		{
			char v;
			v = d.hand[i].getValue();
			if (v == '~')
				std::cout << "|10 | ";
			else
				std::cout << "|" << v << "  | ";
		}

		std::cout << '\n';


		for (int i = 0; i < d.cards; i++)
		{
			char s = d.hand[i].getSuite() + 3;
			std::cout << "| " << s << " | ";
		}

		std::cout << '\n';

		for (int i = 0; i < d.cards; i++)
		{
			char v;
			v = d.hand[i].getValue();
			if (v == '~')
				std::cout << "|_10| ";
			else
				std::cout << "|__" << v << "| ";
		}

		std::cout << '\n';

	}
	return os;
}