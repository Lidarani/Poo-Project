#include<ctime>
#include<random>
#include<Game.h>

//std::string suites[] = {"\u2661", "\u2662", "\u2667", "\u2664"}; // for cout, suite: ♥ - 0, ♦ - 1, ♣ - 2, ♠ - 3;

int main()
{
	srand(time(0));
	Game g;
	int losses = 0;

	while (true)
	{
		while (!g.humanIsBroke())
			g.playGame();

		losses++;
		
		char d = '-';
		short attempts = 0;

		for(; attempts < 10 && d != 'y'; attempts++)
		{
			rlutil::cls();
			std::cout << " You lost all your money.. Wanna try again? y/n\n >";
			
			std::cin >> d;
			if(d == 'n')
				return 0;
		}

		if(d != 'y')
			return 0;

	}
	return 0;
}