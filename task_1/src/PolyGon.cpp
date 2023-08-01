#include "PolyGon.h"

void PolyGon::draw(WDraw& wdraw) const
{
	PolyLine::draw(wdraw);
	wdraw.drawSegment(points[0], points[points.size() - 1]);
}

BoundyBox PolyGon::getBoundyBox() const
{
	Rectangle rect = AABBStrategy().doAlgorithm(points);
	double lenght = this->lengthSeg();

	return BoundyBox("PolyGon", rect, lenght);
}

double PolyGon::lengthSeg() const
{

	double sum = PolyLine::lengthSeg();

	sum += distance(points[0], points[points.size() - 1]);

	return sum;
}
