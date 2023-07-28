#include "Decorator.h"

void Decorator::draw(WDraw& wdraw)
{
	this->object->draw(wdraw);
}

void BoxDrawDecorator::draw(WDraw& wdraw)
{
	Rectangle rect = object->box();
	rect.draw(wdraw);	this->object->draw(wdraw);
}
