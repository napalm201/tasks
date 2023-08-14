#pragma once 

#include "Circle.h"

class ArcCircle : public Circle 
{
public:
	ArcCircle(void);
	ArcCircle(const Point2d& p, double r, double startAngle, double endAng);

	virtual ~ArcCircle(void) = default;

public:
	virtual void draw(WDraw& wdraw) const override;
	virtual BoundyBox getBoundyBox() const override;
	virtual double length() const override;

	virtual void pack(Provider::DataProvider* dataprov) const override;
	virtual void unpack(Provider::DataProvider* dataprov) override;
private:
	double m_dStartAngle = 0;
	double m_dEndAngle = 2 * PI;
};