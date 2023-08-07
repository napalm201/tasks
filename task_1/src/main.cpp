
#include <iostream>
#include "Providers/ObjProvider.h"
#include "WDraw/WDraw.h"
#include "Objects/Figures.h"
#include "Providers/ObjProvider.h"
#include "WConsole/WConsole.h"

double gData[] = {
    8, // -- ����� �������� � �����



    1, // 1 -- ��� "�������" �� ���������, ������������� ���� ���������
    4, // 4 -- ���������� ����� double
    0.0, 0.0, // ���������� - ����� ������ ����
    10.0, 10.0, // ���������� - ������ ������� ����



    2, // 2 -- ��� "����������"
    3, 
    0.0, 0.0, // ���������� - ����� ����������
    25.0, // ������ ����������



    3, // 3 -- ���� ����������� ���
    5,
    1., 2., 3., 4., 5., // ������



    4, // 4 - ���� ����������
    5,
    150., 150.,  // ���������� -- ����� ����������
    44.,         // ������ ����������
    PI/4., PI/2., // ����� -- ������ � ����� ����


    2, // 2 -- ��� "����������"
    3,
    10.0, THROW_ERR, // ��� ������ ������� ���������� ����������
    25.0,



    5, // 5 -- ��� �������������
    10,
    10., 20., // ���������� �����
    20., 30., // ���������� �����
    35., 25., // ���������� �����
    0., 50., // ���������� �����
    0., 0.,   // ���������� �����



    6, // -- ��� "�������"
    10,
    0,0, // ���������� �����
    1,1, // ���������� �����
    0,1, // ���������� �����
    0,2, // ���������� �����
    5,5, // ���������� �����


    28, // ����������� ������
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
