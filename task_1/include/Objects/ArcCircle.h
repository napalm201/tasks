#pragma once 

#include "Circle.h"

class ArcCircle : public Circle 
{
public:
	ArcCircle(void) = default;
	ArcCircle(const Point2d& p, double r, double startAngle, double endAng);

	virtual ~ArcCircle(void) = default;

public:
	virtual void draw(WDraw& wdraw) const override;
	virtual BoundyBox getBoundyBox() const override;
	virtual double length() const override;

	virtual void pack(Provider::DataProvider* dataprov) const override;
	virtual void unpack(Provider::DataProvider* dataprov) override;
private:
	double startAngle = 0;
	double endAngle = 2 * PI;
};