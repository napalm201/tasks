#pragma once

#include "Object.h"
#include "Point2d.h"
#include "Rect.h"

class BoundyBox {

public:
	BoundyBox() = default;
	BoundyBox(const std::string& name, const Rectangle& rect, double length) :
		name(name),
		rect(rect),
		length(length) {}

public:
	virtual void draw(WDraw & wdraw) const;
	
private:
	Rectangle rect = Rectangle(Point2d(0, 0), Point2d(0, 0));
	std::string name;
	double length;
};