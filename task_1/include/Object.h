#pragma once
#include "Point2d.h"
#include "WDraw.h"
#include "Rect.h"

class Object {
public:
	virtual void draw(WDraw& wDraw) = 0;
	virtual Rectangle box() = 0;
};



