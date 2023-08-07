
#include <iostream>
#include "Providers/ObjProvider.h"
#include "WDraw/WDraw.h"
#include "Objects/Figures.h"
#include "Providers/ObjProvider.h"
#include "WConsole/WConsole.h"

double gData[] = {
    8, // -- число объектов в файле



    1, // 1 -- тип "квадрат" со сторонами, параллельными осям координат
    4, // 4 -- количество чисел double
    0.0, 0.0, // координаты - левый нижний угол
    10.0, 10.0, // координаты - правый верхний угол



    2, // 2 -- тип "окружность"
    3, 
    0.0, 0.0, // координаты - центр окружности
    25.0, // радиус окружности



    3, // 3 -- пока неизвестный тип
    5,
    1., 2., 3., 4., 5., // данные



    4, // 4 - дуга окружности
    5,
    150., 150.,  // координаты -- центр окружности
    44.,         // радиус окружности
    PI/4., PI/2., // уголы -- начало и конец дуги


    2, // 2 -- тип "окружность"
    3,
    10.0, THROW_ERR, // при чтении объекта выбросится исключение
    25.0,



    5, // 5 -- тип многоугольник
    10,
    10., 20., // координаты точки
    20., 30., // координаты точки
    35., 25., // координаты точки
    0., 50., // координаты точки
    0., 0.,   // координаты точки



    6, // -- тип "ломаная"
    10,
    0,0, // координаты точки
    1,1, // координаты точки
    0,1, // координаты точки
    0,2, // координаты точки
    5,5, // координаты точки


    28, // неизвестный объект
    10,
    90,91,92,93,94,95,96,97,98,99
};

int main() {

	WDraw& wdraw = WDraw::getWDraw();
    WConsole& wconsole = WConsole::getWConsole();

	Provider::ObjProvider prov(gData, sizeof(gData) / sizeof(gData[0]));

    bool damaged;

	std::vector<std::shared_ptr<Object>> objs = prov.getObject(damaged);

    wdraw.background(0, 0, 0);
	
    for (const auto& obj : objs) {
		obj->draw(wdraw);
        BoundyBoxObject(obj->getBoundyBox(), obj).draw(wdraw);
	}
    
    wdraw.render();

	bool quit = false;

	while (!quit) {
    
        if (wdraw.event.type == CLOSE)
			quit = true;

        if (wconsole.update == true) {

            std::vector<double> data = wconsole.getData();

            prov.setdata(data.data(), data.size());



            wconsole.update = false;

        }

		glfwPollEvents();
	}
}
