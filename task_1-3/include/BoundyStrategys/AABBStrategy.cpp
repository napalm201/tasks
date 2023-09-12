#include "AABBStrategy.h"
#include <cmath>
#include <algorithm>

BoundyBox AABBStrategy::doAlgorithm(const Point2d& min_p, const Point2d& max_p) const
{
	return BoundyBox(min_p, max_p);
}

BoundyBox AABBStrategy::doAlgorithm(const Point2d& p, double r) const
{
	double x1 = p.x() - r;
	double y1 = p.y() - r;
	double x3 = p.x() + r;
	double y3 = p.y() + r;

	Point2d p1 = Point2d(x1, y1);
	Point2d p3 = Point2d(x3, y3);

	return BoundyBox(p1, p3);
}

BoundyBox AABBStrategy::doAlgorithm(const Point2d& p, double r, double startAngle, double endAngle) const
{
	double startPointX = r * std::cos(startAngle) + p.x();
    double startPointY = r * std::sin(startAngle) + p.y();

    double endPointX = r * std::cos(endAngle) + p.x();
	double endPointY = r * std::sin(endAngle) + p.y();

	Point2d startPoint(startPointX, startPointY);
	Point2d endPoint(endPointX, endPointY);

	std::vector<Point2d> pointsCircle;
	pointsCircle.reserve(2);

	pointsCircle.push_back(startPoint);
	pointsCircle.push_back(endPoint);

	double angles[5] = { 0 , PI / 2, PI, 3 * PI / 2,  2 * PI };

	for (int i = 0; i < 4; ++i) {

		double angle = angles[i];

		if (angle > startAngle && angle < endAngle) {

			double pointX = r * std::cos(angle) + p.x();
			double pointY = r * std::sin(angle) + p.y();

			Point2d point(pointX, pointY);
			pointsCircle.push_back(point);
		}

	}

	return doAlgorithm(pointsCircle);

}

BoundyBox AABBStrategy::doAlgorithm(const std::vector<Point2d>& points) const
{
	if (points.size() < 1)
		return BoundyBox();

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
	Point2d p3 = Point2d(maxX, maxY);

	return BoundyBox(p1, p3);
}
