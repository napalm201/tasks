#include "MyAplication.h"
#include "Providers/DataProvider.h"
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
    PI / 4., PI / 2., // ����� -- ������ � ����� ����


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


MyAplication::MyAplication()
{
    objProv.setdata(gData, sizeof(gData) / sizeof(gData[0]));
}

void MyAplication::runTimeConsole()
{
    std::thread thr1(&MyAplication::runTimeWDraw, this);

    while (!quit) {

        std::string userInput;
        
        std::getline(std::cin, userInput);

        if (userInput == "Save") {

            std::cout << "���� ���� ��������� ��������" << std::endl;
            
            std::string patch;
            std::getline(std::cin, patch);

            if (patch == "/q")
                break;

            std::unique_lock<std::mutex> ul(mtx1);
            objProv.saveToFileData(patch);
            ul.unlock();
        }
        else if (userInput == "Read") {

            std::cout << "���� � ����� ��������� ���������" << std::endl;

            std::string patch;
            std::getline(std::cin, patch);

            if (patch == "/q")
                break;

            std::unique_lock<std::mutex> ul(mtx1);
            objProv.readFromFileData(patch);
            update = true;
            ul.unlock();
        }
        else if (userInput == "Exit") {
            std::unique_lock<std::mutex> ul(mtx1);
            quit = true;
            ul.unlock();
        }
        else if(userInput == "Data") {

            std::cout << "������ ���" << std::endl;
            std::cout << "������: 1 - ������� ��'����, 2 - ��� ��'����, 3 - ������� ����� � ��'���, ��� ..." << std::endl;

            std::string data;
            std::getline(std::cin, data);

         	std::vector<double> numbers;
	        std::istringstream is(data);

            try {
                double num;

                while (is >> num) {
                    numbers.push_back(num);
                }

                std::unique_lock<std::mutex> ul(mtx1);
                objProv.setdata(numbers.data(), numbers.size());
                update = true;
                ul.unlock();
            }

            catch (const std::invalid_argument& e) {
                std::cout<< "������� " << e.what() << std::endl;
            }
           
        }
     
   }

   thr1.join();

}

void MyAplication::runTimeWDraw()
{
    WDraw& wdraw = WDraw::getWDraw();

    std::vector<std::shared_ptr<Object>> objs;

    wdraw.background(0, 0, 0);

    while (!quit) {

        if (wdraw.event.type == CLOSE) {
            std::unique_lock<std::mutex> ul(mtx1);
            quit = true;
        }
           
        if (update == true) {

            std::unique_lock<std::mutex> ul(mtx1);
            
            objs = objProv.getObject();

            update = false;
            

            ul.unlock();

            wdraw.background(0, 0, 0);

            for (const auto& obj : objs) {

                obj->draw(wdraw);
                BoundyBoxObject(obj->getBoundyBox(), obj).draw(wdraw);
               
            }

            wdraw.render();
        }

        wdraw.pullevent();

    }

}

MyAplication& MyAplication::getApp()
{
	static MyAplication app; return app;
}
