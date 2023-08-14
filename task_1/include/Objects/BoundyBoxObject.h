#pragma once
#include "BoundyBox.h"
#include "Rectangle.h"
#include <memory>

class BoundyBoxObject : public Object
{
public:
	BoundyBoxObject(void) = default;
	BoundyBoxObject(const BoundyBox& boundy);
	BoundyBoxObject(const BoundyBox& boundy, std::shared_ptr<Object> ptrObj);

	~BoundyBoxObject(void) = default;

	virtual void draw(WDraw & wdraw) const override;
	virtual class BoundyBox getBoundyBox() const override;
	virtual double length() const override;

	virtual void pack(Provider::DataProvider* dataprov) const override;
	virtual void unpack(Provider::DataProvider* dataprov) override;
private:
	Rectangle m_rect;
	std::weak_ptr<Object> m_pObjPtr;
};

