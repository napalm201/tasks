#pragma once
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <vector>
#include <sstream>


class WConsole
{
public:
	WConsole(const WConsole& other) = delete;
	WConsole& operator=(const WConsole& other) = delete;

private:
	WConsole();
	~WConsole();

	static WConsole wconsole;

public:
	
	std::vector<double> getData() const;
	bool update = false;

private:
	void work();
	void runTime();
	void close();

	std::string input;

	std::thread thread1;

	bool quit = false;

public:
	static WConsole& getWConsole();
};

