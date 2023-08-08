#include "Point2d.h"

Point2d::Point2d(double xx, double yy) : m_dX(xx), m_dY(yy)
{
}

Point2d::~Point2d(void)
{
}

double Point2d::x() const
{
    return m_dX; 
}

double Point2d::y() const
{
    return m_dY;
}


double distance(const Point2d& p1, const Point2d& p2) 
{
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();

    return std::sqrt(dx * dx + dy * dy);
}


