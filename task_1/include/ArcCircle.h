#pragma once
#include "Circle.h"
#include <cmath>
#include <vector>
#include "Strategys.h"
#include "BoundyBox.h"

#define PI 3.14

class ArcCircle : public Circle {

public:
	ArcCircle() = default;

	ArcCircle(const Point2d& p, double r, double startAngle, double endAngle)
		: Circle(p, r), startAngle(startAngle), endAngle(endAngle) {}

public:
	virtual void draw(WDraw& wdraw) const override;
	virtual BoundyBox getBoundyBox() const override;
	virtual double lengthSeg() const override;

private:
	double startAngle = 0;
	double endAngle = 2 * PI;
};