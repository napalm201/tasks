#include "Rect.h"

void Rectangle::draw(WDraw& wDraw)
{
	wDraw.fillColor(1, 0, 1);
	wDraw.drawSegment(p1, p2);
	wDraw.drawSegment(p2, p3);
	wDraw.drawSegment(p3, p4);
	wDraw.drawSegment(p4, p1);
}

Rectangle Rectangle::box()
{
	return *this;
}
