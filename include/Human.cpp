#include<Human.h>

Human::Human() : Player()
{
	resetMoney();
	clearHand();
}

Human::Human(const Human& other) : Player(other), money(other.money)
{

};

int Human::getMoney() {return money;}

void Human::addMoney(const int x) {money += x;}

void Human::subMoney(const int x) {money -= x;}

void Human::resetMoney(){money = 5000;}

void Human::clearHand()
{
	hand.clear();
	sum = 0;
	ace = false;
}


std::wostream& operator<<(std::wostream & wos, Human& p) // Human sum + Cards
{
	if (p.sum > 21) //Player card sum or Busted
	{
		std::wcout << "Busted!\n";
	}
	else
		std::wcout << p.sum << '\n';

	for (size_t i = 0; i < p.hand.size(); i++) // top of the cards
		std::wcout << " ___  ";

	std::wcout << '\n';

	for (size_t i = 0; i < p.hand.size(); i++) // first row, |v   | |v   |, v = card number
	{
		char v;
		v = p.hand[i].getValue();

		if (v == '~')
			std::wcout << "|10 | ";
		else
			std::wcout << "|" << v << "  | ";
	}

	std::wcout << '\n';


	for (size_t i = 0; i < p.hand.size(); i++) //2nd row, | s  | |  s |, where s = symbol
	{
		std::wstring s = p.getSymbol(p.hand[i].getSuite());
		std::wcout << "| " << s << " | ";
	}

	std::wcout << '\n';

	for (size_t i = 0; i < p.hand.size(); i++) // last row, |___v| |___v|, v = card number
	{
		char v;
		v = p.hand[i].getValue();		
		if (v == '~')
			std::wcout << "|_10| ";
		else
			std::wcout << "|__" << v << "| ";
	}

	std::wcout << '\n';

	return wos;
}
