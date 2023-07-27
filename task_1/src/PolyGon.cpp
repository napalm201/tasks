#include "PolyGon.h"

void PolyGon::draw(WDraw& wdraw)
{
	PolyLine::draw(wdraw);
	wdraw.drawSegment(points[0], points[points.size() - 1]);
}

Rectangle PolyGon::box()
{
	return PolyLine::box();
}
