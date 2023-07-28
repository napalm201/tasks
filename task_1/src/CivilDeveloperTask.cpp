// CivilDeveloperTask.cpp : Defines the entry point for the console application.
//

#include "DataProvider.h"
#include "Exceptions.h"
#include "ObjProv.h"
#include <tchar.h>
#include <string>


int _tmain(int argc, _TCHAR* argv[])
{
	DataProvider provider;
	ObjProv prov(&provider);

	std::vector<std::shared_ptr<Object>> objs = prov.getObjects();

	WDraw wdraw;
	for (auto& obj : objs) {
		wdraw.drawText("Object");
		obj->draw(wdraw);

		wdraw.drawText("AABB");
		obj->box().draw(wdraw);

		wdraw.drawText("Length");
		wdraw.drawText(std::to_string(obj->lengthSeg()).c_str());
	}

	return 0;
}
