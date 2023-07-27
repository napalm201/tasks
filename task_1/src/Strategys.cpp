#include "Strategys.h"

Rectangle AABBStrategy::doAlgorithm(std::vector<Point2d> points) const
{
    if (points.size() < 1)
        return Rectangle();

    auto comparatorOX = [](const Point2d& point1, const Point2d& point2) {
        return point1.x() > point2.x();
    };

    auto comparatorOY = [](const Point2d& point1, const Point2d& point2) {
        return point1.y() > point2.y();
    };

    auto minPointX = std::min_element(points.begin(), points.end(), comparatorOX);
    auto minPointY = std::min_element(points.begin(), points.end(), comparatorOY);
    auto maxPointX = std::max_element(points.begin(), points.end(), comparatorOX);
    auto maxPointY = std::max_element(points.begin(), points.end(), comparatorOY);

    double minX = (*minPointX).x();
    double maxX = (*maxPointX).x();
    double minY = (*minPointY).y();
    double maxY = (*maxPointY).y();

    Point2d p1 = Point2d(minX, minY);
    Point2d p2 = Point2d(minX, maxY);
    Point2d p3 = Point2d(maxX, maxY);
    Point2d p4 = Point2d(maxX, minY);

    return Rectangle(p1, p2, p3, p4);
}

