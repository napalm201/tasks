#pragma once

#include "Objects/BoundyBox.h"
#include <vector>

#define PI 3.14

class BoundyStrategy
{
public:
    BoundyStrategy() = default;
    virtual ~BoundyStrategy() = default;

public:
    virtual BoundyBox doAlgorithm(const Point2d& p1, const Point2d& p2, const Point2d& p3, const Point2d& p4) const = 0;
    virtual BoundyBox doAlgorithm(const Point2d& p, double r) const = 0;
    virtual BoundyBox doAlgorithm(const Point2d& p, double r, double startAngle, double endAngle) const = 0;
    virtual BoundyBox doAlgorithm(std::vector<Point2d> points) const = 0;
};
