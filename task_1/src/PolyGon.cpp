#include "PolyGon.h"

void PolyGon::draw(WDraw& wdraw)
{
	PolyLine::draw(wdraw);
	wdraw.drawSegment(points[0], points[points.size() - 1]);
}

BoundyBox PolyGon::getBoundyBox() const
{
	return PolyLine::getBoundyBox();
}



double PolyGon::lengthSeg()
{

	double sum = PolyLine::lengthSeg();

	sum += distance(points[0], points[points.size() - 1]);

	return sum;
}
