#include<iostream>
#include<Card.h>

Card::Card()
{
	suite = 0;
	value = 0;
}

Card::Card(const int card)
{
	if (card == 52)
	{
		suite = 0;
		value = 1;
	}
	else
	{
		suite = card / 13;
		value = card == 0 ? 0: card % 13 + 1;
	}
}

Card::Card(const Card& c)
{
	suite = c.suite;
	value = c.value;
}

Card Card::operator=(const Card& c)
{
	if (this == &c)
	{
		return *this;
	}
	suite = c.suite;
	value = c.value;
	return *this;
}

char Card::getValue()
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

int Card::getSuite() {return suite;}

std::wostream& operator<<(std::wostream& os, const Card& c)
{
	std::wcout << c.suite << ' ' << c.value << '\n';
	return os;
}