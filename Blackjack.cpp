#include<ctime>
#include<random>
#include<Game.h>

int main()
{

#ifdef _WIN32
	#include<fcntl.h>
	_setmode(_fileno(stdout), _O_U16TEXT);
#endif

#ifndef _WIN32
	setlocale(LC_ALL, "en_US.utf8");
#endif

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

		for (; attempts < 10 && d != 'y'; attempts++)
		{
			rlutil::cls();
			std::wcout << " You lost all your money.. Wanna try again? y/n\n >";

			std::cin >> d;
			if (d == 'n')
				return 0;
		}

		if (d != 'y')
			return 0;

	}
	return 0;
}