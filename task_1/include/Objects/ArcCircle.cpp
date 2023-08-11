#include "ArcCircle.h"

ArcCircle::ArcCircle(const Point2d& p, double r, double startAngle, double endAng) : 
	Circle(p, r), 
	startAngle(startAngle), 
	endAngle(endAngle)
{
	type = ARCCIRLE;
	count = 5;
}

void ArcCircle::draw(WDraw& wdraw) const
{
	wdraw.fillStroke(34, 34, 34);
	wdraw.wStroke(3);
	wdraw.drawArcCircle(p, r, startAngle, endAngle);
}

BoundyBox ArcCircle::getBoundyBox() const
{
	return boundyAlgorithm->doAlgorithm(p, r, startAngle, endAngle);
}

double ArcCircle::length() const
{
	return (endAngle - startAngle) * r;
}

void ArcCircle::pack(Provider::DataProvider* dataprov) const
{
	Circle::pack(dataprov);

	dataprov->add<double>(startAngle); dataprov->add<double>(endAngle);
}

void ArcCircle::unpack(Provider::DataProvider* dataprov)
{
	Circle::unpack(dataprov);

	startAngle = readFromDataProv(dataprov);
	endAngle = readFromDataProv(dataprov);
}
