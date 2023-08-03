#pragma once
#include <cmath>

class Point2d
{
public:
    Point2d(void) = default;
    Point2d(double xx, double yy);
    virtual ~Point2d(void);
    double x() const;
    double y() const;
private:
    double m_dX = 0;
    double m_dY = 0;
};

double distance(const Point2d& p1, const Point2d& p2);

