#include "PolyLine.h"


void PolyLine::draw(WDraw& wdraw) const
{
    wdraw.fillStroke(56, 56, 65);
    for (int i = 0; i < points.size() - 1; i++) {
        wdraw.drawSegment(points[i], points[i + 1]);
    }
}

BoundyBox PolyLine::getBoundyBox() const
{
    Rectangle rect = AABBStrategy().doAlgorithm(points);
    double lenght = this->lengthSeg();

    return BoundyBox("PolyLine", rect, lenght);
}


double PolyLine::lengthSeg() const
{
    double sum = 0;

    for (int i = 0; i < points.size() - 1; i++) {
        sum += distance(points[i], points[i + 1]);
    }

    return sum;
}

void PolyLine::addPoint(const Point2d& point)
{
    points.push_back(point);
}