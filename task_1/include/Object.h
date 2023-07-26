#pragma once
#include "Point2d.h"
#include "WDraw.h"

class Object {
public:
	virtual void draw(WDraw& wDraw) = 0;
};



