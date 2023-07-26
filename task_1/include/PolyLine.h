#pragma once
#include "Object.h"
#include "Point2d.h"
#include <vector>

class PolyLine : public Object {

public:
	PolyLine() = default;

public:
	virtual void draw(WDraw& wdraw) override;

	void addPoint(const Point2d& point);
private:
	std::vector<Point2d> points;
};