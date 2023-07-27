#include "Circle.h"

void Circle::draw(WDraw& wDraw)
{
	wDraw.fillColor(1, 1, 1);
	wDraw.drawCircle(p, r);
}

Rectangle* Circle::box()
{
	double x1 = p.x() - r;
	double y1 = p.y() - r;
	double x3 = p.x() + r;
	double y3 = p.y() + r;

	return new Rectangle(Point2d(x1, y1), Point2d(x3 , y3));
}
