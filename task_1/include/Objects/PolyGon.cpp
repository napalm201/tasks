#include "PolyGon.h"

PolyGon::PolyGon(void)
{
    m_eType = POLYGON;
    m_nCount = 0;
}

void PolyGon::draw(WDraw& wdraw) const
{
    if (m_nCount == 0 || m_nCount == 1)
        return;

    PolyLine::draw(wdraw);

    wdraw.drawSegment(m_arrPoints[0], m_arrPoints[m_nCount - 1]);
}

BoundyBox PolyGon::getBoundyBox() const
{
	return m_boundyAlgorithm->doAlgorithm(m_arrPoints);
}

double PolyGon::length() const
{
    if (m_nCount == 0 || m_nCount == 1)
        return 0;

    double sum = PolyLine::length();
    
    sum += Point2d::distance(m_arrPoints[0], m_arrPoints[m_nCount - 1]);

    return sum;
}

void PolyGon::pack(Provider::DataProvider* dataprov) const
{
    PolyLine::pack(dataprov);
}

void PolyGon::unpack(Provider::DataProvider* dataprov)
{
    PolyLine::unpack(dataprov);
}

