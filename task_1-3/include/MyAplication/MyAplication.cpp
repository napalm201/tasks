#include "MyAplication.h"
#include "Providers/DataProvider.h"
using namespace Objects;
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
    m_objProv.setdata(gData, sizeof(gData) / sizeof(gData[0]));
    m_arrObjs = m_objProv.getObject();
}

void MyAplication::runTimeConsole()
{
    std::thread thr1(&MyAplication::runTimeWDraw, this);

    while (!m_bQuit) {

        std::string userInput;
        
        std::getline(std::cin, userInput);

        if (userInput == "Save") {
            save();
        }
        else if (userInput == "Read") {
            read();
        }
        else if (userInput == "Data") {
            data();
        }
        else if(userInput == "Exit") {
            exit();
        }
     
   }

   thr1.join();

}

void MyAplication::runTimeWDraw()
{
    WDraw& wdraw = WDraw::getWDraw();

    wdraw.background(0, 0, 0);

    while (!m_bQuit) {

        if (wdraw.event.type == CLOSE) {
            std::unique_lock<std::mutex> ul(m_mtx1);
            m_bQuit = true;
        }
           
        if (m_bUpdate == true || wdraw.event.type == RESIZE) {

            wdraw.event.type = UNDEF;

            std::unique_lock<std::mutex> ul(m_mtx1);

            m_bUpdate = false;
            
            ul.unlock();

            wdraw.background(0, 0, 0);

            for (const auto& obj : m_arrObjs) {

                obj->draw(wdraw);
                BoundyBoxObject(obj->getBoundyBox(), obj).draw(wdraw);
               
            }

            wdraw.render();
        }
      
        wdraw.pullevent();

    }

}

void MyAplication::save()
{
    std::cout << "���� ���� ��������� ��������" << std::endl;

    std::string patch;
    std::getline(std::cin, patch);

    if (patch == "/q")
        return;

    std::unique_lock<std::mutex> ul(m_mtx1);

    m_objProv.setdata(m_arrObjs);

    m_objProv.saveToFileData(patch);

    ul.unlock();
}

void MyAplication::read()
{
    std::cout << "���� � ����� ��������� ���������" << std::endl;

    std::string patch;
    std::getline(std::cin, patch);

    if (patch == "/q")
        return;

    std::unique_lock<std::mutex> ul(m_mtx1);

    m_objProv.readFromFileData(patch);

    m_arrObjs = m_objProv.getObject();

    m_bUpdate = true;

    ul.unlock();
}

void MyAplication::data()
{
    std::cout << "������ ���" << std::endl;

    std::string data;
    std::getline(std::cin, data);

    std::vector<double> numbers;
    std::istringstream is(data);

    try {
        double num;

        while (is >> num) {
            numbers.push_back(num);
        }

        std::unique_lock<std::mutex> ul(m_mtx1);

        m_objProv.setdata(numbers.data(), numbers.size());
        m_bUpdate = true;
        m_arrObjs = m_objProv.getObject();

        ul.unlock();

    }

    catch (const std::invalid_argument& e) {
        std::cout << "������� " << e.what() << std::endl;
    }

}

void MyAplication::exit()
{

    std::unique_lock<std::mutex> ul(m_mtx1);

    m_bQuit = true;

    ul.unlock();
}

MyAplication& MyAplication::getApp()
{
	static MyAplication m_app; return m_app;
}
