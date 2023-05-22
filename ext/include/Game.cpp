#include<Game.h>
#include<cstring>

int Game::readBet()
{
	bet = 0;
	char s[100] = "";

	std::cin >> s;

	int len = strlen(s);
	for (int i = 0; i < len; i++)
		if (!isdigit(s[i]))
			return -1;
		else
			bet = bet * 10 + s[i] - '0';

	if (bet <= human.getMoney())
		return 1;

	bet = 0;
	return 0;

}

void Game::setBet(int x)
{
	bet = x;
}

Game::Game()
{
	human.setMoney(5000);
	int cond = 2;
	int att = 0;

	while (true)
	{
		rlutil::cls();
		std::cout << " Rules: \n Try to get as close to 21 without going over. \n Kings, Queens, and Jacks are worth 10 points. \n Aces are worth 1 or 11 points. \n Cards 2 through 10 are worth their face value \n (H)it to take another card. \n (S)tand to stop taking cards \n In case of a tie, the bet is returned to the player. \n The dealer stops hitting at 17.\n\n Money: " << human.getMoney() << "\n\n";

		if (att == 25)
		{
			setBet(human.getMoney());
			cond = 1;
		}

		if (cond == -1)
			std::cout << " Please provide a valid number!\n";
		else if (cond == 0)
			std::cout << " Not enough money!\n";
		if (cond == 1)
		{
			Round r(dealer, human, bet);
			att = 0;

			if (human.getMoney() == 0)
			{
				rlutil::cls();
				std::cout << "You lost all your money! Want to try again? y/n\n";
				break;
			}

			else
			{
				rlutil::cls();
				std::cout << " Rules: \n Try to get as close to 21 without going over. \n Kings, Queens, and Jacks are worth 10 points. \n Aces are worth 1 or 11 points. \n Cards 2 through 10 are worth their face value \n (H)it to take another card. \n (S)tand to stop taking cards \n In case of a tie, the bet is returned to the player. \n The dealer stops hitting at 17.\n\n Money: " << human.getMoney() << "\n\n";
			}
		}

		std::cout << " How much do you bet?\n >";

		cond = readBet();
		att++;
	}
}