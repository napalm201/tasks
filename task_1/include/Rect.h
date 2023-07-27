#pragma once

#include "WDraw.h"
#include "Point2d.h"
#include "Object.h"
#include "utility"

class Rectangle : public Object
{
public:
	Rectangle() = default;

	Rectangle(const Point2d& p1, const Point2d& p3)
		: p1(p1), p3(p3) {
		p2 = Point2d(p1.x(), p3.y());
	    p4 = Point2d(p3.x(), p1.y());
	}


	Rectangle(const Point2d& p1, const Point2d& p2,
		const Point2d& p3, const Point2d& p4)
		: p1(p1), p2(p2), p3(p3), p4(p4) {}

	Rectangle(Point2d&& p1, Point2d&& p2,
		Point2d&& p3, Point2d&& p4) :
		p1(std::move(p1)), p2(std::move(p2)),
		p3(std::move(p3)), p4(std::move(p4)) {}

public:
	virtual void draw(WDraw& wDraw) override;
	virtual Rectangle box() override;
	virtual void transform(const Point2d& center);

private:
	Point2d p1 = Point2d(-1, 0); Point2d p2 = Point2d(0, 1);
	Point2d p3 = Point2d(0, 1); Point2d p4 = Point2d(0, -1);
};