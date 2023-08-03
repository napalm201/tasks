#include "Circle.h"

Circle::Circle(const Point2d& p, double r) : 
	p(p),
	r(r)
{
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
