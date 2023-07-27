#include "ArcCircle.h"

void ArcCircle::draw(WDraw& wdraw)
{
	wdraw.fillColor(0, 0, 0);
	wdraw.drawArcCircle(p, r, startAngle, endAngle);
}

Rectangle ArcCircle::box()
{
	std::vector<Point2d> points = {Point2d(std::cos(startAngle), std::sin(startAngle)) ,
		Point2d(std::cos(endAngle), std::sin(endAngle))};
	double angles[5] = {0 , PI / 2, PI, 3 * PI / 2,  2 * PI};

	for (int i = 0; i < 4; i ++) {
		double angle = angles[i];
		if (angle > startAngle && angle < endAngle) {
			points.push_back(Point2d(std::cos(angle), std::sin(angle)));
		}
	}

	//Поки працює від стартових кутів: 0 до 2п

	return AABBStrategy().doAlgorithm(points);
}
