// CivilDeveloperTask.cpp : Defines the entry point for the console application.
//

#include "DataProvider.h"
#include "ObjProv.h"
#include "WDraw.h"
#include "Decorator.h"

#include <tchar.h>
#include <string>

class Drawer {
public:
	Drawer(const std::vector<std::shared_ptr<Object>>& objects, WDraw& wdraw)
		: objects(objects), wdraw(wdraw) { }

	void draw() {

		for (const auto& obj : objects) 
			BoxDrawDecorator(obj.get()).draw(wdraw);
		

		glfwSwapBuffers(wdraw.window);
	}

private:
    WDraw& wdraw;
	const std::vector<std::shared_ptr<Object>>& objects;
};


int _tmain(int argc, _TCHAR* argv[])
{
	DataProvider provider;
	ObjProv prov(&provider);
	WDraw wdraw;

	std::vector<std::shared_ptr<Object>> objs = prov.getObjects();
	Drawer drawer(objs, wdraw);

	drawer.draw();

	bool quit = false;

	while (!quit) {

		quit = wdraw.getStateWindow();
		glfwPollEvents();

	}

	return 0;
}
