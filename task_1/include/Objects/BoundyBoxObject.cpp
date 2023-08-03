#include "BoundyBoxObject.h"

BoundyBoxObject::BoundyBoxObject(const BoundyBox& boundy) : rect(boundy)
{
}

BoundyBoxObject::BoundyBoxObject(const BoundyBox& boundy, std::shared_ptr<Object> ptrObj) : rect(boundy), objPtr(ptrObj)
{
}

void BoundyBoxObject::draw(WDraw& wdraw) const
{
	rect.draw(wdraw);
}

BoundyBox BoundyBoxObject::getBoundyBox() const
{
	return rect.getBoundyBox();
}

double BoundyBoxObject::length() const
{
	return rect.length();
}
