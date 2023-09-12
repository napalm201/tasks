#pragma once
#include "BoundyStrategy.h"

class AABBStrategy : public BoundyStrategy
{
public: 
	AABBStrategy(void) = default;
	~AABBStrategy(void) = default;

public:
	virtual BoundyBox doAlgorithm(const Point2d& min_p, const Point2d& max_p) const override;
	virtual BoundyBox doAlgorithm(const Point2d& p, double r) const override;
	virtual BoundyBox doAlgorithm(const Point2d& p, double r, double startAngle, double endAngle) const override;
	virtual BoundyBox doAlgorithm(const std::vector<Point2d>& points) const override;
};

