#pragma once
#include "Object.h"
#include "Point2d.h"
#include "Rect.h"
#include "Strategys.h"
#include <vector>

class PolyLine : public Object {
public:
	PolyLine() = default;

public:
	virtual void draw(WDraw& wdraw) override;
	virtual Rectangle box() override;

	void addPoint(const Point2d& point);
protected:
	std::vector<Point2d> points;
};