#include<Human.h>

Human::Human()
{
	money = 5000;
}

int Human::getMoney() {return money;}

void Human::setMoney(const int x) {money = x;}

void Human::clearHand()
{
	for(int i = 0; i < cards; i++)
		hand[i] = Card(0);
	cards = 0;
	sum = 0;
	ace = false;
}


std::ostream& operator<<(std::ostream & os, Human& p)
{
	if (p.sum > 21)
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

		if (v == '~')
			std::cout << "|10 | ";
		else
			std::cout << "|" << v << "  | ";
	}

	std::cout << '\n';


	for (int i = 0; i < p.cards; i++)
	{
		char s = p.hand[i].getSuite() + 3;
		std::cout << "| " << s << " | ";
	}

	std::cout << '\n';

	for (int i = 0; i < p.cards; i++)
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
