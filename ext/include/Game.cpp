#include<Game.h>
#include<string>

Game::Game()
{
	r.resetRound();
	outRules();
}

void Game::outRules()
{
	rlutil::cls();
	std::cout << " Rules:\n"
	          << "Try to get as close to 21 without going over.\n"
	          << "Kings, Queens, and Jacks are worth 10 points.\n"
	          << "Aces are worth 1 or 11 points.\n"
	          << "Cards 2 throug 10 are worth their face value\n"
	          << "(H)it to take another card.\n"
	          << "(S)tand to stop taking cards\n"
	          << "In case of a tie, the bet is returned to the player.\n"
	          << "The dealer stops hitting at 17.\n\n"
	          << "Money: " << r.getHMoney() << "\n\n";
}

void Game::readBet()
{
	outRules();
	bet = 0;
	std::string s;

	for (short i = 0; i < 10; i++)
	{
		std::cout << "How much you want to bet?\n >";
		std::cin >> s;

		try
		{
			if(s.size() > 9)
				throw std::out_of_range("Out of range");

			size_t pos;
			int aux;
			aux = std::stoi(s, &pos);

			outRules();

			if (pos != s.size())
				throw std::invalid_argument("Invalid argument");

			if (aux <= r.getHMoney())
			{
				bet = aux;
				return;
			}
			else
			{
				std::cout << "Not enough money!\n";
			}
		}

		catch (std::invalid_argument&)
		{
			outRules();
			std::cout << "Not a number, try again maybe?\n";
		}

		catch (std::out_of_range&)
		{
			outRules();
			std::cout << "You'd wish to have that much money, huh?\n"
			          << " Cause I sure do.. \n";
		}
	}
}

void Game::playGame()
{
	while (!r.getHMoney())
	{
		readBet();
		r.resetRound();
		r.playRound(bet);
	}

	if (r.brokeHuman())
		return;

}

bool Game::humanIsBroke()
{
	return r.brokeHuman();
}