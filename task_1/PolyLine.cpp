#include "PolyLine.h"


void PolyLine::draw(WDraw& wdraw)
{
    for (int i = 0; i < points.size() - 1; i++) {
        wdraw.drawSegment(points[i], points[i + 1]);
    }
}

void PolyLine::addPoint(const Point2d& point)
{
    points.push_back(point);
}