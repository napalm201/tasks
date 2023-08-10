#include "Circle.h"

Circle::Circle(const Point2d& p, double r) : 
	p(p),
	r(r)
{
	type = CIRCLE;
}

void Circle::draw(WDraw& wDraw) const
{
	wDraw.fillStroke(34, 34, 34);
	wDraw.wStroke(3);
	wDraw.drawCircle(p, r);
}

BoundyBox Circle::getBoundyBox() const
{
	return boundyAlgorithm->doAlgorithm(p ,r);
}

double Circle::length() const
{
	return 2 * PI * r;
}

void Circle::pack(Provider::DataProvider* dataprov) const
{
	dataprov->add<int>(type);
	dataprov->add<int>(3);
	dataprov->add<double>(p.x()); dataprov->add<double>(p.y());
	dataprov->add<double>(r);
}

void Circle::unpack(Provider::DataProvider* dataprov)
{
	const int countNumbers = dataprov->rd<int>();

	double x = readFromDataProv(dataprov); double y = readFromDataProv(dataprov);
	p = Point2d(x, y);

     r = readFromDataProv(dataprov);

}
