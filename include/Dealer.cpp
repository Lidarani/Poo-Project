#include<Dealer.h>
#include<fstream>

Dealer::Dealer() : Player()
{
	hiddenCard = true; // Dealer only
	hand.clear();
	sum = 0;
	ace = false;
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

std::wostream& operator<<(std::wostream & wos, Dealer &d)
{
	// Daca avem carte ascunsa inseamnca ca dealer-ul are doar 2 carti
	// Afisam pentru prima ### si apoi pe a 2-a carte

	if (d.hiddenCard)
	{
		char v = d.hand[1].getValue();
		std::wstring s = d.getSymbol(d.hand[1].getSuite());
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
		std::wcout << "???\n"
		           << " ___   ___\n"
		           << "|###| |" << convertWString(strUp) << " |\n"
		           << "|###| | " << s << " |\n"
		           << "|###| |_" << convertWString(strDown) << "|\n";
	}

	else
	{
		if (d.sum == 21 && d.hand.size() == 2)
			std::wcout << "Blackjack!!\n"; //afisarea total Dealer

		else if (d.sum > 21)
			std::wcout << "Busted!\n"; //afisare total Dealer

		else
			std::wcout << d.sum << '\n'; //afisare total Dealer

		for (size_t i = 0; i < d.hand.size(); i++)
			std::wcout << " ___  ";

		std::wcout << '\n';

		for (size_t i = 0; i < d.hand.size(); i++)
		{
			char v;
			v = d.hand[i].getValue();
			if (v == '~')
				std::wcout << "|10 | ";
			else
				std::wcout << "|" << v << "  | ";
		}

		std::wcout << '\n';


		for (size_t i = 0; i < d.hand.size(); i++)
		{
			std::wstring s = d.getSymbol(d.hand[i].getSuite());
			std::wcout << "| " << s << " | ";
		}

		std::wcout << '\n';

		for (size_t i = 0; i < d.hand.size(); i++)
		{
			char v;
			v = d.hand[i].getValue();
			if (v == '~')
				std::wcout << "|_10| ";
			else
				std::wcout << "|__" << v << "| ";
		}

		std::wcout << '\n';

	}
	return wos;
}