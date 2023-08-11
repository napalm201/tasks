#include "PolyGon.h"

PolyGon::PolyGon(void)
{
    type = POLYGON;
    count = 0;
}

void PolyGon::draw(WDraw& wdraw) const
{
    wdraw.fillStroke(56, 56, 65);

    for (int i = 0; i < points.size() - 1; i++) 
        wdraw.drawSegment(points[i], points[i + 1]);
    

    wdraw.drawSegment(points[0], points[points.size() - 1]);
}

BoundyBox PolyGon::getBoundyBox() const
{
	return boundyAlgorithm->doAlgorithm(points);
}

double PolyGon::length() const
{
    double sum = 0;

    for (int i = 0; i < points.size() - 1; i++) 
        sum += distance(points[i], points[i + 1]);
    
    sum += distance(points[0], points[points.size() - 1]);

    return sum;
}

void PolyGon::pack(Provider::DataProvider* dataprov) const
{
    dataprov->add<int>(type);
    dataprov->add<int>(points.size());
    
    for (const Point2d& point : points)
        point.pack(dataprov);
}

void PolyGon::unpack(Provider::DataProvider* dataprov)
{
    const int counter = dataprov->rd<int>();
    
    for (int i = 0; i < counter / 2; i++) 
    {
        Point2d p;
        p.unpack(dataprov, isDamaged);
        addPoint(p);
    }

}

void PolyGon::addPoint(const Point2d point)
{
    points.push_back(point);
    count++;
}
