#pragma once

#include "Objects/BoundyBox.h"
#include <vector>


class BoundyStrategy
{
public:
    BoundyStrategy() = default;
    virtual ~BoundyStrategy() = default;

public:
    virtual BoundyBox doAlgorithm(const Point2d& min_p, const Point2d& max_p) const = 0;
    virtual BoundyBox doAlgorithm(const Point2d& p, double r) const = 0;
    virtual BoundyBox doAlgorithm(const Point2d& p, double r, double startAngle, double endAngle) const = 0;
    virtual BoundyBox doAlgorithm(const std::vector<Point2d>& points) const = 0;
};
