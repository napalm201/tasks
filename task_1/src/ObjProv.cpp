#include "ObjProv.h"


std::vector<std::shared_ptr<Object>> ObjProv::getObjects() {

	ReadFactory ReadFactory(dataprov);
	std::vector<std::shared_ptr<Object>> objects;

	try {
		int countObject = dataprov->rdInt();	
		while (true) 
			objects.push_back(ReadFactory.factory(dataprov->rdInt()));
	}
	catch(const ReadError& e) {
		e.wait();
	}
	catch (const EndOfFile& e) {
		e.wait();
	}
	catch (const UnderfindObj& e) {
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
		else if (type == 3) {
            throw UnderfindObj();
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
			throw ReadError();
		}
	
}

std::shared_ptr<Object> ObjProv::ReadFactory::greateRect()
{
	int countCordinate = dataprov->rdInt();


	if (countCordinate == 4) {

		Point2d p1(dataprov->rdDouble(), dataprov->rdDouble());
		Point2d p3(dataprov->rdDouble(), dataprov->rdDouble());

		return std::shared_ptr<Object>(new Rectangle(p1, p3));
	}
	else if (countCordinate == 8) {

		Point2d p1(dataprov->rdDouble(), dataprov->rdDouble());
		Point2d p2(dataprov->rdDouble(), dataprov->rdDouble());
		Point2d p3(dataprov->rdDouble(), dataprov->rdDouble());
		Point2d p4(dataprov->rdDouble(), dataprov->rdDouble());

		return std::shared_ptr<Object>(new Rectangle(p1, p2, p3, p4));
	}
	else {
		throw ReadError();
	}
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
	int countPoint = dataprov->rdInt();

	PolyGon* polygon = new PolyGon;

	for (int i = 0; i < countPoint; i++)
		polygon->addPoint(Point2d(dataprov->rdDouble(), dataprov->rdDouble()));


	return std::shared_ptr<Object>(polygon);
}

std::shared_ptr<Object> ObjProv::ReadFactory::greatePolyLine()
{
	int countPoint = dataprov->rdInt();

	PolyLine* polyline = new PolyLine;

	for (int i = 0; i < countPoint; i++)
		polyline->addPoint(Point2d(dataprov->rdDouble(), dataprov->rdDouble()));

	return std::shared_ptr<Object>(polyline);
}
