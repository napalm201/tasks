#pragma once
#include "Object.h"
#include "Point2d.h"

class Circle : public Objects {
public:
	Circle() = default;

	Circle(const Point2d p, double r) : p(p), r(r) {}

public:
	virtual void draw(WDraw& wDraw) override;

protected:
	Point2d p = Point2d(0, 0);
	double r = 2;
};