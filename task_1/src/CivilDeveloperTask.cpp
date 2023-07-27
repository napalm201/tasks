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

	std::vector<std::shared_ptr<Object>> objs = prov.getObjects();

	WDraw wdraw;
	for (auto& obj : objs) {
		obj->box()->draw(wdraw);
	}

	return 0;
}
