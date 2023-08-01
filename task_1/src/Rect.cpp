#include "Rect.h"
#include "BoundyBox.h"

void Rectangle::draw(WDraw& wDraw) const
{
	wDraw.fillStroke(1, 0, 1);
	double w = p4.x() - p1.x();
	double h = p2.y() - p1.y();
	wDraw.drawRect(p1, w, h);
}


double Rectangle::lengthSeg() const
{
	double sum = 0;
	sum += 2 * distance(p1, p2);
	sum += 2 * distance(p2, p3);
	return sum;
}

BoundyBox Rectangle::getBoundyBox() const
{
	double lenght = this->lengthSeg();
	return BoundyBox("Rect", * this, lenght);
}




void Rectangle::transform(const Point2d& center)
{

}
