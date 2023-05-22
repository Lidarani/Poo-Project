#include<ctime>
#include<random>
#include<Game.h>

//std::string suites[] = {"\u2661", "\u2662", "\u2667", "\u2664"}; // for cout, suite: ♥ - 0, ♦ - 1, ♣ - 2, ♠ - 3;
 
int main()
{
	srand(time(0));
	int attempt = 0;
	Game g;

	while (true)
	{
		char d = '-';
		std::cin >> d;

		if(attempt == 10)
			d = 'n';

		if (d == 'y')
		{
			Game g2;
			attempt = 0;
		}
		else if (d == 'n')
			break;
		else
		{
			rlutil::cls();
			std::cout << " You lost all your money! Want to try again? y/n\n ";
			attempt++;
		}
	}

	return 0;
} 	