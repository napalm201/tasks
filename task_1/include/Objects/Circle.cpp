#include "Circle.h"

Circle::Circle(const Point2d& p, double r) : 
	p(p),
	r(r)
{
	type = CIRCLE;
	count = 3;
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
	dataprov->add<int>(count);

	p.pack(dataprov);

    dataprov->add<double>(r);
}

void Circle::unpack(Provider::DataProvider* dataprov)
{
    count = dataprov->rd<int>();

	p.unpack(dataprov, isDamaged);

    r = readFromDataProv(dataprov);

}
