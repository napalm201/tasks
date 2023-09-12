#include "ArcCircle.h"
namespace Objects {

	ArcCircle::ArcCircle(void)
	{
		m_eType = ARCCIRLE;
		m_nCount = 5;
	}

	ArcCircle::ArcCircle(const Point2d& p, double r, double startAngle, double endAngle) :
		Circle(p, r),
		m_dStartAngle(startAngle),
		m_dEndAngle(endAngle)
	{
		m_eType = ARCCIRLE;
		m_nCount = 5;
	}

	void ArcCircle::draw(WDraw& wdraw) const
	{
		wdraw.fillStroke(34, 34, 34);
		wdraw.wStroke(3);
		wdraw.drawArcCircle(m_p, m_dr, m_dStartAngle, m_dEndAngle);
	}

	BoundyBox ArcCircle::getBoundyBox() const
	{
		return m_boundyAlgorithm->doAlgorithm(m_p, m_dr, m_dStartAngle, m_dEndAngle);
	}

	double ArcCircle::length() const
	{
		return (m_dEndAngle - m_dStartAngle) * m_dr;
	}

	void ArcCircle::pack(Provider::DataProvider* dataprov) const
	{
		Circle::pack(dataprov);

		dataprov->add<double>(m_dStartAngle); dataprov->add<double>(m_dEndAngle);
	}

	void ArcCircle::unpack(Provider::DataProvider* dataprov)
	{
		Circle::unpack(dataprov);

		m_dStartAngle = readFromDataProv(dataprov);
		m_dEndAngle = readFromDataProv(dataprov);
	}

}