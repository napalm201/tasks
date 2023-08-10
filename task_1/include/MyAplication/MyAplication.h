#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>

#include "Providers/ObjProvider.h"
#include "WDraw/WDraw.h"
#include "Objects/Figures.h"
#include "Providers/ObjProvider.h"


class MyAplication
{
public:
	MyAplication(const MyAplication& other) = delete;
	MyAplication& operator=(const MyAplication& other) = delete;

	void runTimeConsole();

private:
	MyAplication();
	~MyAplication() = default;

	static MyAplication app;

private:
	void runTimeWDraw();

	std::mutex mtx1;

	bool update = true;
	bool quit = false;
	std::vector<std::shared_ptr<Object>> objs;
	Provider::ObjProvider objProv;

public:
	static MyAplication&  getApp();
};

