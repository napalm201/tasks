#include "ObjProv.h"


ObjProv::ObjProv(DataProvider* dataprov)
{
		ObjProv::dataprov = dataprov;
}

ObjProv::ReadFactory::ReadFactory(DataProvider* dataprov) : dataprov(dataprov)
{
}

std::vector<std::shared_ptr<Object>> ObjProv::getObjects() {

	ReadFactory ReadFactory(dataprov);
	std::vector<std::shared_ptr<Object>> objects;

	try {
		int countObject = dataprov->rdInt();

		for (int i = 0; i < countObject; i++) {

			int type = dataprov->rdInt();

			std::shared_ptr<Object> obj = ReadFactory.factory(type);

			if (obj == nullptr)
				readNextObject();
			else
				objects.push_back(obj);

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
		else {
			return nullptr;
		}
}

double ObjProv::ReadFactory::readFromData(bool& isDamaged)
{
	try {
		return dataprov->rdDouble();
	}
	catch (const ReadError& e) {
		e.wait();
		isDamaged = true;
		return 0.0;
	}
}

std::shared_ptr<Object> ObjProv::ReadFactory::greateRect()
{
	int countCordinate = dataprov->rdInt();
	bool damaged = false;

	Point2d p1(readFromData(damaged), readFromData(damaged));
	Point2d p3(readFromData(damaged), readFromData(damaged));

	Rectangle* rect = new Rectangle(p1, p3);
	rect->isDamaged = damaged;

	return std::shared_ptr<Object>(rect);

}

std::shared_ptr<Object> ObjProv::ReadFactory::greateCircle()
{
	int countNumbers = dataprov->rdInt();
	bool damaged = false;

	Point2d p(readFromData(damaged), readFromData(damaged));
	double r = readFromData(damaged);

	Circle* circle = new Circle(p, r);
	circle->isDamaged = damaged;

	return std::shared_ptr<Object>(circle);
}

std::shared_ptr<Object> ObjProv::ReadFactory::greateArcCircle()
{

	int countNumbers = dataprov->rdInt();
	bool damaged = false;

	Point2d p(readFromData(damaged), readFromData(damaged));
	double r = readFromData(damaged);

	double startAngle = readFromData(damaged);
	double endAngle = readFromData(damaged);

	ArcCircle* arc = new ArcCircle(p, r, startAngle, endAngle);
	arc->isDamaged = damaged;

	return std::shared_ptr<Object>(arc);
}

std::shared_ptr<Object> ObjProv::ReadFactory::greatePolygon()
{
	int countNumber = dataprov->rdInt();
	bool damaged = false;

	PolyGon* polygon = new PolyGon;

	for (int i = 0; i < countNumber / 2; i++)
		polygon->addPoint(Point2d(readFromData(damaged), readFromData(damaged)));

	polygon->isDamaged = damaged;

	return std::shared_ptr<Object>(polygon);
}

std::shared_ptr<Object> ObjProv::ReadFactory::greatePolyLine()
{
	int countNumber = dataprov->rdInt();
	bool damaged = false;

	PolyLine* polyline = new PolyLine;

	for (int i = 0; i < countNumber / 2; i++)
		polyline->addPoint(Point2d(readFromData(damaged), readFromData(damaged)));

	polyline->isDamaged = damaged;

	return std::shared_ptr<Object>(polyline);
}

void ObjProv::readNextObject()
{
	int counter = dataprov->rdInt();

	double foo;

	for (int i = 0; i < counter; i ++) 
		foo = dataprov->rdInt();
	
}
