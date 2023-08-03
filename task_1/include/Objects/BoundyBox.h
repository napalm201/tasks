#pragma once
#include "Point2d.h"

class BoundyBox 
{
public:
	BoundyBox(void) = default;
	BoundyBox(const Point2d& p1, const Point2d& p2);
	BoundyBox(const Point2d& p1, const Point2d& p2, const Point2d& p3, const Point2d& p4);
	virtual ~BoundyBox(void) = default;

public:
	Point2d p1() const;
	Point2d p2() const;
	Point2d p3() const;
	Point2d p4() const;

private:
	Point2d m_p1 = Point2d(0, 0);
	Point2d m_p2 = Point2d(0, 0);
	Point2d m_p3 = Point2d(0, 0);
	Point2d m_p4 = Point2d(0, 0);
};