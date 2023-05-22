#ifndef CARD_H
#define CARD_H

#include<iostream>

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

	void setValue(int v);

	void setSuite(int s);

	friend std::ostream& operator<<(std::ostream& os, const Card& c);
	
};

#endif