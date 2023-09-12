#pragma once 

#include "Object.h"
#include "BoundyBox.h"
#include <utility>

namespace Objects {

	class Rectangle : public Object
	{
	public:
		Rectangle(void);

		Rectangle(const Point2d& min_p, const Point2d& max_p);

		Rectangle(const BoundyBox& boundy);

		virtual	~Rectangle(void) = default;

	public:
		virtual void draw(WDraw& wDraw) const override;
		virtual BoundyBox getBoundyBox() const override;
		virtual double length() const override;

		virtual void pack(Provider::DataProvider* dataprov) const override;
		virtual void unpack(Provider::DataProvider* dataprov) override;

	private:
		Point2d m_min_p = Point2d(-1, -1);
		Point2d m_max_p = Point2d(1, 1);
	};
}