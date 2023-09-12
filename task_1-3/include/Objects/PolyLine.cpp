#include "PolyLine.h"

namespace Objects {

    PolyLine::PolyLine(void)
    {
        m_eType = POLYLINE;
        m_nCount = 0;
    }

    void PolyLine::draw(WDraw& wdraw) const
    {
        wdraw.fillStroke(56, 0, 65);

        for (int i = 0; i < m_nCount - 1; ++i) {
            wdraw.drawSegment(m_arrPoints[i], m_arrPoints[i + 1]);
        }
    }

    BoundyBox PolyLine::getBoundyBox() const
    {
        return m_boundyAlgorithm->doAlgorithm(m_arrPoints);
    }

    double PolyLine::length() const
    {
        double sum = 0;

        for (int i = 0; i < m_nCount - 1; ++i)
            sum += Point2d::distance(m_arrPoints[i], m_arrPoints[i + 1]);

        return sum;
    }

    void PolyLine::pack(Provider::DataProvider* dataprov) const
    {
        dataprov->add<int>(m_eType);
        dataprov->add<int>(m_nCount * 2);

        for (const Point2d& point : m_arrPoints)
            point.pack(dataprov);
    }

    void PolyLine::unpack(Provider::DataProvider* dataprov)
    {
        const int counter = dataprov->rd<int>();

        for (int i = 0; i < counter / 2; ++i)
        {
            Point2d p;
            p.unpack(dataprov, m_bDamaged);
            addPoint(p);
        }
    }

    void PolyLine::addPoint(const Point2d& point)
    {
        m_arrPoints.push_back(point);
        m_nCount++;
    }
}