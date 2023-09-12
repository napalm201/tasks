#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>

#include "Providers/ObjProvider.h"
#include "WDraw/WDraw.h"
#include "Objects/Figures.h"

using namespace Objects;

class MyAplication
{
public:
	MyAplication(const MyAplication& other) = delete;
	MyAplication& operator=(const MyAplication& other) = delete;

	void runTimeConsole();

private:
	MyAplication();
	~MyAplication() = default;

	static MyAplication m_app;

private:
	void runTimeWDraw();

	void save();
	void read();
	void data();
	void exit();

	std::mutex m_mtx1;

	bool m_bUpdate = true;
	bool m_bQuit = false;

	std::vector<std::shared_ptr<Object>> m_arrObjs;
	Provider::ObjProvider m_objProv;

public:
	static MyAplication&  getApp();
};

