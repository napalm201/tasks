#include "ObjProv.h"


ObjProv::ObjProv(DataProvider* dataprov)
{
		ObjProv::dataprov = dataprov;

		unorderType.insert(3);
		unorderType.insert(28);
}

std::vector<std::shared_ptr<Object>> ObjProv::getObjects() {

	ReadFactory ReadFactory(dataprov);
	std::vector<std::shared_ptr<Object>> objects;

	try {
		int countObject = dataprov->rdInt();

		while (true) {

			int type = dataprov->rdInt();

			if (unorderType.find(type) == unorderType.end())
				objects.push_back(ReadFactory.factory(type));
			else 
				readNextObject();
		}
	}
	catch(const ReadError& e) {
		e.wait();
	}
	catch (const EndOfFile& e) {
		e.wait();
	}

	return objects;

}

ObjProv::ReadFactory::ReadFactory(DataProvider* dataprov) : dataprov(dataprov)
{
}

std::shared_ptr<Object> ObjProv::ReadFactory::factory(int type)
{
		if (type == 1) {
			return greateRect();
		}
		else if (type == 2){
			return greateCircle();
		}
		else if (type == 4) {
			return greateArcCircle();
		}
		else if (type == 5) {
			return greatePolygon();
		}
		else if (type == 6) {
			return greatePolyLine();
		}
}

std::shared_ptr<Object> ObjProv::ReadFactory::greateRect()
{
	int countCordinate = dataprov->rdInt();

	Point2d p1(dataprov->rdDouble(), dataprov->rdDouble());
	Point2d p3(dataprov->rdDouble(), dataprov->rdDouble());

	return std::shared_ptr<Object>(new Rectangle(p1, p3));

}

std::shared_ptr<Object> ObjProv::ReadFactory::greateCircle()
{
	int countNumbers = dataprov->rdInt();

	Point2d p(dataprov->rdDouble(), dataprov->rdDouble());
	double r = dataprov->rdDouble();

	return std::shared_ptr<Object>(new Circle(p, r));
}

std::shared_ptr<Object> ObjProv::ReadFactory::greateArcCircle()
{

	int countNumbers = dataprov->rdInt();

	Point2d p(dataprov->rdDouble(), dataprov->rdDouble());
	double r = dataprov->rdDouble();

	double startAngle = dataprov->rdDouble();
	double endAngle = dataprov->rdDouble();

	return std::shared_ptr<Object>(new ArcCircle(p, r, startAngle, endAngle));
}

std::shared_ptr<Object> ObjProv::ReadFactory::greatePolygon()
{
	int countNumber = dataprov->rdInt();

	PolyGon* polygon = new PolyGon;

	for (int i = 0; i < countNumber / 2; i++)
		polygon->addPoint(Point2d(dataprov->rdDouble(), dataprov->rdDouble()));


	return std::shared_ptr<Object>(polygon);
}

std::shared_ptr<Object> ObjProv::ReadFactory::greatePolyLine()
{
	int countNumber = dataprov->rdInt();

	PolyLine* polyline = new PolyLine;

	for (int i = 0; i < countNumber / 2; i++)
		polyline->addPoint(Point2d(dataprov->rdDouble(), dataprov->rdDouble()));

	return std::shared_ptr<Object>(polyline);
}

void ObjProv::readNextObject()
{
	int counter = dataprov->rdInt();

	double foo;

	for (int i = 0; i < counter; i ++) {
		foo = dataprov->rdInt();
	}
}
