#pragma once
#include "Object.h"

#define PI 3.14

class Circle : public Object {
public:
	Circle(void) = default;
	Circle(const Point2d& p, double r);

	virtual ~Circle(void) = default;

public:
	virtual void draw(WDraw& wDraw) const override;
	virtual BoundyBox getBoundyBox() const override;
	virtual double length() const override;


	virtual void pack(Provider::DataProvider* dataprov) const override;

protected:
	Point2d p = Point2d(0, 0);
	double r = 2;
};