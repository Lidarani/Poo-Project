#include<iostream>

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
		if (this == &c)
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