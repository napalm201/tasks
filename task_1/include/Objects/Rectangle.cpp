#include "Rectangle.h"

Rectangle::Rectangle(const Point2d& p1, const Point2d& p3) : 
	  p1(p1), 
	  p3(p3) 
{
	p2 = Point2d(p1.x(), p3.y());
	p4 = Point2d(p3.x(), p1.y());
}

Rectangle::Rectangle(const Point2d& p1, const Point2d& p2, const Point2d& p3, const Point2d& p4) :
     p1(p1), 
	 p2(p2),
	 p3(p3), 
	 p4(p4) 
{
}

Rectangle::Rectangle(Point2d&& p1, Point2d&& p2, Point2d&& p3, Point2d&& p4) : 
	p1(std::move(p1)), 
	p2(std::move(p2)),
	p3(std::move(p3)), 
	p4(std::move(p4))
{
}

Rectangle::Rectangle(const BoundyBox& boundy) : 
	p1(boundy.p1()),
	p2(boundy.p2()),
	p3(boundy.p3()),
	p4(boundy.p4())
{

}

void Rectangle::draw(WDraw& wDraw) const
{
	wDraw.fillStroke(67, 0, 0);
	double w = p4.x() - p1.x();
	double h = p2.y() - p1.y();
	wDraw.drawRect(p1, w, h);
}

BoundyBox Rectangle::getBoundyBox() const
{
	return boundyAlgorithm->doAlgorithm(p1, p2, p3, p4);
}

double Rectangle::length() const
{
	double sum = 0;
	sum += 2 * distance(p1, p2);
	sum += 2 * distance(p2, p3);
	return sum;
}
