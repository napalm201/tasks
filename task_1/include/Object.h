#pragma once
#include "Point2d.h"
#include "WDraw.h"

class Object {
public:
	virtual void draw(WDraw& wDraw) = 0;
	virtual class Rectangle box() = 0;
	virtual double lengthSeg() = 0;
};



