#include "PolyGon.h"
#include <vector>

class PolyLine : public PolyGon
{
public:
	PolyLine(void);
	virtual ~PolyLine(void) = default;

public:
	virtual void draw(WDraw& wdraw) const override;
	virtual BoundyBox getBoundyBox() const override;
	virtual double length() const override;

	virtual void pack(Provider::DataProvider* dataprov) const override;
	virtual void unpack(Provider::DataProvider* dataprov) override;
};