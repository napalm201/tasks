#include "DataProvider.h"

void Provider::DataProvider::reset()
{
	c = 0;
}

void Provider::DataProvider::clear()
{
	bytes.clear();
	reset();
}

void Provider::DataProvider::save(const std::string& patch)
{
}

void Provider::DataProvider::read(const std::string& patch)
{
}
