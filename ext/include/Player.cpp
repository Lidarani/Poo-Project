#include<Player.h>

Player::Player()
{
	sum = 0;
	cards = 0;
	ace = false;
}

int Player::getSum() {return sum;}

void Player::drawCard(int card) //Based on deck from Round
{
	int s = card / 13;
	int v = card == 0 ? 0 : card % 13 + 1;
	if (card == 52)
	{
		s = 0;
		v = 1;
	}
	hand[cards].setSuite(s);
	hand[cards].setValue(v);
	cards++;

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
