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

void Point2d::pack(Provider::DataProvider* dataprov) const
{
    dataprov->add<double>(m_dX); dataprov->add<double>(m_dY);
}

void Point2d::unpack(Provider::DataProvider* dataprov, bool& damaged)
{
    damaged = false;

    try {
        m_dX = dataprov->rd<double>(); m_dY = dataprov->rd<double>();
    }catch(const ReadError& er) {
        damaged = true;
    }
    catch (const EndOfFile& er) {
        throw er;
    }
}

double Point2d::distance(const Point2d& p1, const Point2d& p2)
{
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();

    return std::sqrt(dx * dx + dy * dy);
}





