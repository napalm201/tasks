#include "PolyLine.h"

PolyLine::PolyLine(void)
{
    type = POLYLINE;
    count = 0;
}

void PolyLine::draw(WDraw& wdraw) const
{
    wdraw.fillStroke(56, 0, 65);

    for (int i = 0; i < points.size() - 1; i++) {
        wdraw.drawSegment(points[i], points[i + 1]);
    }
}

BoundyBox PolyLine::getBoundyBox() const
{
	return boundyAlgorithm->doAlgorithm(points);
}

double PolyLine::length() const
{
    double sum = 0;

    for (int i = 0; i < points.size() - 1; i++) 
        sum += distance(points[i], points[i + 1]);
    
    return sum;
}

void PolyLine::pack(Provider::DataProvider* dataprov) const
{
    PolyGon::pack(dataprov);
}

void PolyLine::unpack(Provider::DataProvider* dataprov)
{
    PolyGon::unpack(dataprov);
}
