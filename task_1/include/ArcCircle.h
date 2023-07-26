#pragma once
#include "Circle.h"
class ArcCircle : public Circle {

public:
	ArcCircle() = default;

	ArcCircle(const Point2d p, double r, double startAngle, double endAngle)
		: Circle(p, r), startAngle(startAngle), endAngle(endAngle) {}

public:
	virtual void draw(WDraw& wdraw) override;
private:
	double startAngle = 0;
	double endAngle = 2 * PI;
};
