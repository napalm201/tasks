#include "PolyLine.h"

PolyLine::PolyLine(void)
{
    type = POLYLINE;
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

    for (int i = 0; i < points.size() - 1; i++) {
        sum += distance(points[i], points[i + 1]);
    }

    return sum;
}

void PolyLine::pack(Provider::DataProvider* dataprov) const
{
    dataprov->add<int>(type);
    dataprov->add<int>(points.size());
    
    for (const Point2d& point : points) {
        dataprov->add<double>(point.x()); dataprov->add<double>(point.y());
    }

}

void PolyLine::addPoint(const Point2d& point)
{
    points.push_back(point);
}
