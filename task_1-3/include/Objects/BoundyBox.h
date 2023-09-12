#pragma once
#include "Point2d.h"

class BoundyBox 
{
public:
	BoundyBox(void) = default;
	BoundyBox(const Point2d& min_p, const Point2d& max_p);
	virtual ~BoundyBox(void) = default;

public:
	const Point2d& minP() const;
	const Point2d& maxP() const;

private:
	Point2d m_min_p = Point2d(0, 0);
	Point2d m_max_p = Point2d(0, 0);
};