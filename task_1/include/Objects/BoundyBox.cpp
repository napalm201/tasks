#include "BoundyBox.h"

BoundyBox::BoundyBox(const Point2d& min_p, const Point2d& max_p) :
	m_min_p(min_p),
	m_max_p(max_p)
{
}

const Point2d& BoundyBox::minP() const
{
	return m_min_p;
}

const Point2d& BoundyBox::maxP() const
{
	return m_max_p;
}
