#include "BoundyBox.h"

BoundyBox::BoundyBox(const Point2d& p1, const Point2d& p3) :
	m_p1(p1),
	m_p3(p3)
{
	m_p2 = Point2d(p1.x(), p3.y());
	m_p4 = Point2d(p3.x(), p1.y());
}

BoundyBox::BoundyBox(const Point2d& p1, const Point2d& p2, const Point2d& p3, const Point2d& p4) : m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4)
{
}

Point2d BoundyBox::p1() const
{
	return m_p1;
}

Point2d BoundyBox::p2() const
{
	return m_p2;
}

Point2d BoundyBox::p3() const
{
	return m_p3;
}

Point2d BoundyBox::p4() const
{
	return m_p4;
}
