#include<Dealer.h>
#include<fstream>

Dealer::Dealer() : Player()
{
	hiddenCard = true;
	clearHand();
}

Dealer::Dealer(const Dealer& other) : Player(other), hiddenCard(other.hiddenCard)
{

};

void Dealer::openCard() //show the blank dealer card
{
	hiddenCard = false;
}

void Dealer::clearHand()
{
	hiddenCard = true; // Dealer only
	hand.clear();
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
		if(d.sum == 21 && d.hand.size() == 2)
			std::cout << "Blackjack!!\n"; //afisarea total Dealer

		else if (d.sum > 21)
			std::cout << "Busted!\n"; //afisare total Dealer

		else
			std::cout << d.sum << '\n'; //afisare total Dealer

		for (size_t i = 0; i < d.hand.size(); i++)
			std::cout << " ___  ";

		std::cout << '\n';

		for (size_t i = 0; i < d.hand.size(); i++)
		{
			char v;
			v = d.hand[i].getValue();
			if (v == '~')
				std::cout << "|10 | ";
			else
				std::cout << "|" << v << "  | ";
		}

		std::cout << '\n';


		for (size_t i = 0; i < d.hand.size(); i++)
		{
			char s = d.hand[i].getSuite() + 3;
			std::cout << "| " << s << " | ";
		}

		std::cout << '\n';

		for (size_t i = 0; i < d.hand.size(); i++)
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