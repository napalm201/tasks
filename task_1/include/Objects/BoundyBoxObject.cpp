#include "BoundyBoxObject.h"

BoundyBoxObject::BoundyBoxObject(const BoundyBox& boundy) : m_rect(boundy)
{
	m_eType = UND;
}

BoundyBoxObject::BoundyBoxObject(const BoundyBox& boundy, std::shared_ptr<Object> ptrObj) : m_rect(boundy), m_pObjPtr(ptrObj)
{

}

void BoundyBoxObject::draw(WDraw& wdraw) const
{
	m_rect.draw(wdraw);
}

BoundyBox BoundyBoxObject::getBoundyBox() const
{
	return m_rect.getBoundyBox();
}

double BoundyBoxObject::length() const
{
	return m_rect.length();
}

void BoundyBoxObject::pack(Provider::DataProvider* dataprov) const
{
	//TODO
}

void BoundyBoxObject::unpack(Provider::DataProvider* dataprov)
{
	//TODO
}
