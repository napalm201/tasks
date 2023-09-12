#pragma once
#include <cmath>
#include "Providers/DataProvider.h"

class Point2d
{
public:
    Point2d(void) = default;
    Point2d(double xx, double yy);
    ~Point2d(void);
    double x() const;
    double y() const;

    void pack(Provider::DataProvider* dataprov) const;
    void unpack(Provider::DataProvider* dataprov, bool &damaged);

    static double distance(const Point2d& p1, const Point2d& p2);

private:
    double m_dX = 0;
    double m_dY = 0;
};


