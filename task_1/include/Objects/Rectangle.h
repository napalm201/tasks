#pragma once 

#include "Object.h"
#include "BoundyBox.h"
#include <utility>

class Rectangle : public Object
{
public:
	Rectangle(void);

	Rectangle(const Point2d& p1, const Point2d& p3);

	Rectangle(const Point2d& p1, const Point2d& p2,
		const Point2d& p3, const Point2d& p4);

	Rectangle(Point2d&& p1, Point2d&& p2,
		Point2d&& p3, Point2d&& p4);

	Rectangle(const BoundyBox& boundy);

    virtual	~Rectangle(void) = default;

public:
	virtual void draw(WDraw& wDraw) const override;
	virtual BoundyBox getBoundyBox() const override;
	virtual double length() const override;

	virtual void pack(Provider::DataProvider* dataprov) const override;

private:
	Point2d p1 = Point2d(-1, 0); Point2d p2 = Point2d(0, 1);
	Point2d p3 = Point2d(0, 1); Point2d p4 = Point2d(0, -1);
};