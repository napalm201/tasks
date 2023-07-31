
#pragma once
#include "Object.h"
#include "BoundyBox.h"

class Decorator : public Object
{
public:
	Decorator() = default;
	Decorator(Object* object) : object(object) {}

	virtual void draw(WDraw& wdraw) override;

protected:
	Object* object;
};

class BoxDrawDecorator : public Decorator {
public:
	BoxDrawDecorator(Object* object) : Decorator(object) {}

	virtual void draw(WDraw& wdraw) override;

};
