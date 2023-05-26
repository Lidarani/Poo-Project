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


std::ostream& operator<<(std::ostream & os, Human& p) // Human sum + Cards
{
	if (p.sum > 21) //Player card sum or Busted
	{
		std::cout << "Busted!\n";
	}
	else
		std::cout << p.sum << '\n';

	for (size_t i = 0; i < p.hand.size(); i++) // top of the cards
		std::cout << " ___  ";

	std::cout << '\n';

	for (size_t i = 0; i < p.hand.size(); i++) // first row, |v   | |v   |, v = card number
	{
		char v;
		v = p.hand[i].getValue();

		if (v == '~')
			std::cout << "|10 | ";
		else
			std::cout << "|" << v << "  | ";
	}

	std::cout << '\n';


	for (size_t i = 0; i < p.hand.size(); i++) //2nd row, | s  | |  s |, where s = symbol
	{
		char s = p.hand[i].getSuite() + 3;
		std::cout << "| " << s << " | ";
	}

	std::cout << '\n';

	for (size_t i = 0; i < p.hand.size(); i++) // last row, |___v| |___v|, v = card number
	{
		char v;
		v = p.hand[i].getValue();		
		if (v == '~')
			std::cout << "|_10| ";
		else
			std::cout << "|__" << v << "| ";
	}

	std::cout << '\n';

	return os;
}
