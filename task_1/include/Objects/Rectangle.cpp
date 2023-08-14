#include "Rectangle.h"

namespace Objects {
	Rectangle::Rectangle(void)
	{
		m_eType = RECT;
		m_nCount = 4;
	}

	Rectangle::Rectangle(const Point2d& min_p, const Point2d& max_p) :
		m_min_p(min_p),
		m_max_p(max_p)
	{

	}


	Rectangle::Rectangle(const BoundyBox& boundy) :
		m_min_p(boundy.minP()),
		m_max_p(boundy.maxP())
	{

	}

	void Rectangle::draw(WDraw& wDraw) const
	{
		wDraw.fillStroke(67, 0, 0);

		double w = m_max_p.x() - m_min_p.x();
		double h = m_max_p.y() - m_min_p.y();

		wDraw.drawRect(m_min_p, w, h);
	}

	BoundyBox Rectangle::getBoundyBox() const
	{
		return m_boundyAlgorithm->doAlgorithm(m_min_p, m_max_p);
	}

	double Rectangle::length() const
	{

		double w = m_max_p.x() - m_min_p.x();
		double h = m_max_p.y() - m_min_p.y();

		return 2 * w + 2 * h;
	}

	void Rectangle::pack(Provider::DataProvider* dataprov) const
	{
		dataprov->add<int>(m_eType);
		dataprov->add<int>(m_nCount);

		m_min_p.pack(dataprov);
		m_max_p.pack(dataprov);

	}

	void Rectangle::unpack(Provider::DataProvider* dataprov)
	{
		m_nCount = dataprov->rd<int>();

		m_min_p.unpack(dataprov, m_bDamaged);
		m_max_p.unpack(dataprov, m_bDamaged);

	}

}