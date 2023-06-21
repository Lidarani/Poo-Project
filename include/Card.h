#ifndef CARD_H
#define CARD_H

#include<Unicode.h>

class Card
{
	int suite, value;

public:
	Card();

	explicit Card(const int card);

	Card(const Card& c);

	Card operator=(const Card& c);

	char getValue();

	int getSuite();

	friend std::wostream& operator<<(std::wostream& os, const Card& c);
	
};

#endif