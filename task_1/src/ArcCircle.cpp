#include "ArcCircle.h"

void ArcCircle::draw(WDraw& wdraw)
{
	wdraw.fillColor(0, 0, 0);
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

	//Поки працює від стартових кутів: 0 до 2п

	Rectangle rect = AABBStrategy().doAlgorithm(points);

	return BoundyBox(rect);
}


double ArcCircle::lengthSeg()
{
	return ( endAngle - startAngle ) * r;
}
