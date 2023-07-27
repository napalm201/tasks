#pragma once
#include "Point2d.h"
#include "WDraw.h"

class Rectangle;

class Object {
public:
	virtual void draw(WDraw& wDraw) = 0;
	virtual Rectangle box() = 0;
};



