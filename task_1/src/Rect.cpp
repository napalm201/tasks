#include "Rect.h"
#include "BoundyBox.h"

void Rectangle::draw(WDraw& wDraw)
{
	wDraw.fillColor(1, 0, 1);
	wDraw.drawSegment(p1, p2);
	wDraw.drawSegment(p2, p3);
	wDraw.drawSegment(p3, p4);
	wDraw.drawSegment(p4, p1);
}


double Rectangle::lengthSeg()
{
	double sum = 0;
	sum += 2 * distance(p1, p2);
	sum += 2 * distance(p2, p3);
	return sum;
}

BoundyBox Rectangle::getBoundyBox() const
{
	return BoundyBox(*this);
}




void Rectangle::transform(const Point2d& center)
{

}
