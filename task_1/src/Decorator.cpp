#include "Decorator.h"

void Decorator::draw(WDraw& wdraw) const
{
	this->object->draw(wdraw);
}

BoundyBox Decorator::getBoundyBox() const
{
	return this->object->getBoundyBox();
}

double Decorator::lengthSeg() const
{
	return this->object->lengthSeg();
}

void BoxDrawDecorator::draw(WDraw& wdraw) const
{
	object->getBoundyBox().draw(wdraw);
	this->object->draw(wdraw);
}
