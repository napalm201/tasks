// CivilDeveloperTask.cpp : Defines the entry point for the console application.
//

#include "DataProvider.h"
#include "Exceptions.h"
#include "ObjProv.h"
#include <tchar.h>


int _tmain(int argc, _TCHAR* argv[])
{
	DataProvider provider;
	ObjProv prov(&provider);
	std::vector<std::shared_ptr<Object>> obj = prov.getObjects();
	return 0;
}
