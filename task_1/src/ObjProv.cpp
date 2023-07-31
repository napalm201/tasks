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
		const int countObject = dataprov->rdInt();

		for (int i = 0; i < countObject; i++) {

			const int type = dataprov->rdInt();

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



std::shared_ptr<Object> ObjProv::ReadFactory::factory(const int type)
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
	const int countCordinate = dataprov->rdInt();
	bool damaged = false;

	double x = readFromData(damaged); double y = readFromData(damaged);
	Point2d p1(x, y);

	x = readFromData(damaged); y = readFromData(damaged);
	Point2d p3(x, y);

	Rectangle rect(p1, p3);
	rect.isDamaged = damaged;

	return std::make_shared<Rectangle>(rect);

}

std::shared_ptr<Object> ObjProv::ReadFactory::greateCircle()
{
	const int countNumbers = dataprov->rdInt();
	bool damaged = false;

	double x = readFromData(damaged); double y = readFromData(damaged);
	Point2d p(x, y);

	double r = readFromData(damaged);

	Circle circle(p, r);
	circle.isDamaged = damaged;

	return std::make_shared<Circle>(circle);
}

std::shared_ptr<Object> ObjProv::ReadFactory::greateArcCircle()
{

	const int countNumbers = dataprov->rdInt();
	bool damaged = false;
	
	double x = readFromData(damaged); double y = readFromData(damaged);
	Point2d p(x, y);
	
	double r = readFromData(damaged);

	double startAngle = readFromData(damaged);
	double endAngle = readFromData(damaged);

	ArcCircle arc(p, r, startAngle, endAngle);
	arc.isDamaged = damaged;

	return std::make_shared<ArcCircle>(arc);
}

std::shared_ptr<Object> ObjProv::ReadFactory::greatePolygon()
{
	const int countNumber = dataprov->rdInt();
	bool damaged = false;

	PolyGon polygon;
	double x, y;

	for (int i = 0; i < countNumber / 2; i++) {
		x = readFromData(damaged); y = readFromData(damaged);
		polygon.addPoint(Point2d(x, y));
	}

	polygon.isDamaged = damaged;

	return std::make_shared<PolyGon>(polygon);
}

std::shared_ptr<Object> ObjProv::ReadFactory::greatePolyLine()
{
	const int countNumber = dataprov->rdInt();
	bool damaged = false;

	PolyLine polyline;
	double x, y;

	for (int i = 0; i < countNumber / 2; i++) {
		x = readFromData(damaged); y = readFromData(damaged);
		polyline.addPoint(Point2d(x ,y));
	}

	polyline.isDamaged = damaged;

	return std::make_shared<PolyLine>(polyline);
}

void ObjProv::readNextObject()
{
	int counter = dataprov->rdInt();

	double foo;

	for (int i = 0; i < counter; i ++) 
		foo = dataprov->rdInt();
	
}
