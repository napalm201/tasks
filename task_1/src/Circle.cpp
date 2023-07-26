#include "Circle.h"

void Circle::draw(WDraw& wDraw)
{
	wDraw.fillColor(1, 1, 1);
	wDraw.drawCircle(p, r);
}
