#include "Circle.h"

namespace Objects {

	Circle::Circle(void)
	{
		m_eType = CIRCLE;
		m_nCount = 3;
	}

	Circle::Circle(const Point2d& p, double r) :
		m_p(p),
		m_dr(r)
	{
		m_eType = CIRCLE;
		m_nCount = 3;
	}

	void Circle::draw(WDraw& wDraw) const
	{
		wDraw.fillStroke(34, 34, 34);
		wDraw.wStroke(3);
		wDraw.drawCircle(m_p, m_dr);
	}

	BoundyBox Circle::getBoundyBox() const
	{
		return m_boundyAlgorithm->doAlgorithm(m_p, m_dr);
	}

	double Circle::length() const
	{
		return 2 * PI * m_dr;
	}

	void Circle::pack(Provider::DataProvider* dataprov) const
	{
		dataprov->add<int>(m_eType);
		dataprov->add<int>(m_nCount);

		m_p.pack(dataprov);

		dataprov->add<double>(m_dr);
	}

	void Circle::unpack(Provider::DataProvider* dataprov)
	{
		m_nCount = dataprov->rd<int>();

		m_p.unpack(dataprov, m_bDamaged);

		m_dr = readFromDataProv(dataprov);

	}

}
