#include<iostream>
#include "Card.h"

Card::Card()
{
	suite = 0;
	value = 0;
}

Card::Card(const int card)
{
	suite = card / 13;
	if (suite > 3)
		suite = 3;
	value = card == 0 ? 0 : card % 13 + 1;
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

void Card::setValue(int v) {value = v;}

void Card::setSuite(int s) {suite = s;}

std::ostream& operator<<(std::ostream& os, const Card& c)
{
	std::cout << c.suite << ' ' << c.value << '\n';
	return os;
}