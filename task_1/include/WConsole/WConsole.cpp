#include "WConsole.h"
#include <condition_variable>

WConsole::WConsole()
{
	runTime();
}

WConsole::~WConsole()
{
	close();
}

void WConsole::runTime()
{
	thread1 = std::thread(&WConsole::work, this);
}

std::vector<double> WConsole::getData() const
{
	std::vector<double> numbers;
	std::istringstream is(input);

	int num;

	while (is >> num) {
		numbers.push_back(num);
	}

	return numbers;
}

void WConsole::close()
{
	quit = true;

	thread1.join();

}


void WConsole::work()
{
	while (!quit) {

		std::getline(std::cin, input);

		update = true;
	}

}

WConsole& WConsole::getWConsole()
{
	static WConsole wconsole; return wconsole;
}
