#include "ArcCircle.h"

void ArcCircle::draw(WDraw& wdraw) const
{
	wdraw.fillStroke(54, 66, 0);
	wdraw.drawArcCircle(p, r, startAngle, endAngle);
}

BoundyBox ArcCircle::getBoundyBox() const
{
	std::vector<Point2d> points = { Point2d(r * std::cos(startAngle) + p.x(), r * std::sin(startAngle) + p.y()) ,
	Point2d(r * std::cos(endAngle) + p.x(), r * std::sin(endAngle) + p.y()) };

	double angles[5] = { 0 , PI / 2, PI, 3 * PI / 2,  2 * PI };

	for (int i = 0; i < 4; i++) {

		double angle = angles[i];

		if (angle > startAngle && angle < endAngle) {
			points.push_back(Point2d(r * std::cos(angle) + p.x(), r * std::sin(angle) + p.y()));
		}
	}

	Rectangle rect = AABBStrategy().doAlgorithm(points);
	double lenght = this->lengthSeg();

	return BoundyBox("Arc", rect, lenght);
}


double ArcCircle::lengthSeg() const
{
	return (endAngle - startAngle) * r;
}