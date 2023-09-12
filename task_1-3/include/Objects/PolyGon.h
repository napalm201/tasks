#pragma once
#include "PolyLine.h"

namespace Objects {

	class PolyGon : public PolyLine
	{
	public:
		PolyGon(void);
		virtual ~PolyGon(void) = default;

	public:
		virtual void draw(WDraw& wdraw) const override;
		virtual BoundyBox getBoundyBox() const override;
		virtual double length() const override;

		virtual void pack(Provider::DataProvider* dataprov) const override;
		virtual void unpack(Provider::DataProvider* dataprov) override;
	};

}