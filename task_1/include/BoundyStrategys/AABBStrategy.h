#pragma once
#include "BoundyStrategy.h"

class AABBStrategy : public BoundyStrategy
{
public: 
	AABBStrategy(void) = default;
	~AABBStrategy(void) = default;

public:
	virtual BoundyBox doAlgorithm(const Point2d& p1, const Point2d& p2, const Point2d& p3, const Point2d& p4) const override;
	virtual BoundyBox doAlgorithm(const Point2d& p, double r) const override;
	virtual BoundyBox doAlgorithm(const Point2d& p, double r, double startAngle, double endAngle) const override;
	virtual BoundyBox doAlgorithm(std::vector<Point2d> points) const override;
};

