#pragma once
#include "Rect.h"
#include <vector>
#include "Point2d.h"

class Strategy {

public:
    Strategy() = default;

public:
    virtual ~Strategy() = default;
    virtual Rectangle doAlgorithm(std::vector<Point2d> points) const = 0;
};


class AABBStrategy : public Strategy {

public:
    AABBStrategy() = default;

public:
    virtual Rectangle doAlgorithm(std::vector<Point2d> points) const override;
};