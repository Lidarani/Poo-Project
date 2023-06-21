#include<Player.h>

Player::Player()
{
	sum = 0;
	ace = false;
}

Player::Player(const Player& other)
{
	sum = other.sum;
	for (size_t i = 0; i < other.hand.size(); i++)
		hand[i] = other.hand[i];
	ace = other.ace;
}

int Player::getSum() {return sum;}

std::wstring Player::getSymbol(int suite)
{
	std::wstring s = symbols[suite];
	return s;
}

void Player::drawCard(int card) //Based on deck from Round
{
	Card aux(card);
	hand.push_back(aux);

	int v = (card == 0) ? 0 : card % 13 + 1;
	if (!v);
	else if (v == 1)
	{
		if (sum <= 10)
		{
			ace = true;
			sum += 11;
		}
		else sum++;
	}
	else if (v <= 10)
		sum += v;
	else
		sum += 10;

	if (sum > 21 && ace)
	{
		ace = false;
		sum -= 10;
	}
}
