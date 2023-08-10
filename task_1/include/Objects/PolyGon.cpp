#include "PolyGon.h"

PolyGon::PolyGon(void)
{
    type = POLYGON;
}

void PolyGon::draw(WDraw& wdraw) const
{
    wdraw.fillStroke(56, 56, 65);

    for (int i = 0; i < points.size() - 1; i++) {
        wdraw.drawSegment(points[i], points[i + 1]);
    }

    wdraw.drawSegment(points[0], points[points.size() - 1]);
}

BoundyBox PolyGon::getBoundyBox() const
{
	return boundyAlgorithm->doAlgorithm(points);
}

double PolyGon::length() const
{
    double sum = 0;

    for (int i = 0; i < points.size() - 1; i++) {
        sum += distance(points[i], points[i + 1]);
    }

    sum += distance(points[0], points[points.size() - 1]);

    return sum;
}

void PolyGon::pack(Provider::DataProvider* dataprov) const
{
    dataprov->add<int>(type);
    dataprov->add<int>(points.size());
    
    for (const Point2d& point : points) {
        dataprov->add<double>(point.x()); dataprov->add<double>(point.y());
    }
}

void PolyGon::unpack(Provider::DataProvider* dataprov)
{
    const int countNumber = dataprov->rd<int>();

    double x, y;
    for (int i = 0; i < countNumber / 2; i++) {
        x = readFromDataProv(dataprov); y = readFromDataProv(dataprov);
        addPoint(Point2d(x, y));
    }

}

void PolyGon::addPoint(const Point2d point)
{
    points.push_back(point);
}
