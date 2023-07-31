#pragma once

#include "Object.h"
#include "Point2d.h"
#include "Rect.h"

class BoundyBox {
public:
	BoundyBox() = default;
	BoundyBox(const Rectangle& rect) : rect(rect) {}

public:
	Rectangle getRectangle() const;

private:
	Rectangle rect = Rectangle(Point2d(0, 0), Point2d(0, 0));
	int size = 0;
};