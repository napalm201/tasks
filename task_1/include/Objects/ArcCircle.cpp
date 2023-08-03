#include "ArcCircle.h"

ArcCircle::ArcCircle(const Point2d& p, double r, double startAngle, double endAng) : 
	Circle(p, r), 
	startAngle(startAngle), 
	endAngle(endAngle)
{
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
