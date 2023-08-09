#include "ArcCircle.h"

ArcCircle::ArcCircle(const Point2d& p, double r, double startAngle, double endAng) : 
	Circle(p, r), 
	startAngle(startAngle), 
	endAngle(endAngle)
{
	type = ARCCIRLE;
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
	dataprov->add<int>(type);
	dataprov->add<int>(5);
	dataprov->add<double>(p.x()); dataprov->add<double>(p.y());
	dataprov->add<double>(r);
	dataprov->add<double>(startAngle); dataprov->add<double>(endAngle);
}
