#include "Object.h"
#include <vector>

class PolyLine : public Object
{
public:
	PolyLine(void);
	virtual ~PolyLine(void) = default;

public:
	virtual void draw(WDraw& wdraw) const override;
	virtual BoundyBox getBoundyBox() const override;
	virtual double length() const override;

	virtual void pack(Provider::DataProvider* dataprov) const override;

	void addPoint(const Point2d& point);

protected:
	std::vector<Point2d> points;
};