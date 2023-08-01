#include "Circle.h"

void Circle::draw(WDraw& wDraw) const
{
	wDraw.fillStroke(54, 1, 1);
	wDraw.drawCircle(p, r);
}

BoundyBox Circle::getBoundyBox() const
{
	double x1 = p.x() - r;
	double y1 = p.y() - r;
	double x3 = p.x() + r;
	double y3 = p.y() + r;

	Rectangle rect(Point2d(x1, y1), Point2d(x3, y3));
	double lenght = this->lengthSeg();

	return BoundyBox("Circle", rect, lenght);
}


double Circle::lengthSeg() const
{
	return 2 * PI * r;
}
