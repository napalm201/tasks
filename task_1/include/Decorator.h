
#pragma once
#include "Object.h"
#include "Rect.h"

class Decorator : public Object
{
public:
	Decorator() = default;
	Decorator(Object* object) : object(object) {}

	virtual void draw(WDraw& wdraw) override {
		 this->object->draw(wdraw);
	}

protected:
	Object* object;
};

class BoxDrawDecorator : public Decorator {
public:
	BoxDrawDecorator(Object* object) : Decorator(object) {}

	virtual void draw(WDraw& wdraw) override {
		Rectangle rect = object->box();
		rect.draw(wdraw);	this->object->draw(wdraw);
	}

};
