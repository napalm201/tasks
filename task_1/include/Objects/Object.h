#pragma once

#include "BoundyBox.h"
#include "WDraw/WDraw.h"
#include "BoundyStrategys/BoundyStrategy.h"
#include "BoundyStrategys/AABBStrategy.h"
#include "Providers/DataProvider.h"
#include <memory>

enum TypeObj {
	UND = 0,
	RECT,
	CIRCLE,
	ARCCIRLE = 4,
	POLYGON,
	POLYLINE
};

class Object 
{
public:
	Object(void) = default;
	virtual ~Object(void) = default;

public:
	virtual void draw(WDraw& wdraw) const = 0;
	virtual class BoundyBox getBoundyBox() const = 0;
	virtual double length() const = 0;

	virtual void pack(Provider::DataProvider* dataprov) const = 0;

public:
	bool isDamaged = 0;

protected:
	TypeObj type;
	std::shared_ptr<BoundyStrategy> boundyAlgorithm = std::make_unique<AABBStrategy>();
};
