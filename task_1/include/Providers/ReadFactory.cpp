#include "ReadFactory.h"

namespace Provider {

	ReadFactory::ReadFactory(DataProvider* dataprov) : dataprov(dataprov)
	{

	}

	std::shared_ptr<Object> ReadFactory::factory(const int type)
	{
		if (type == 1) {
			return greateRect();
		}
		else if (type == 2) {
			return greateCircle();
		}
		else if (type == 4) {
			return greateArcCircle();
		}
		else if (type == 5) {
			return greatePolygon();
		}
		else if (type == 6) {
			return greatePolyLine();
		}
		else {
			return nullptr;
		}
	}


	double ReadFactory::readFromData(bool& isDamaged)
	{
		try {
			return dataprov->rd<double>();
		}
		catch (const ReadError& e) {
			e.wait();
			isDamaged = true;
			return 0.0;
		}
		catch (const EndOfFile& e) {
			throw;
		}
	}


	std::shared_ptr<Object> ReadFactory::greateRect()
	{
		const int countCordinate = dataprov->rd<int>();
		bool damaged = false;

		double x = readFromData(damaged); double y = readFromData(damaged);
		Point2d p1(x, y);

		x = readFromData(damaged); y = readFromData(damaged);
		Point2d p3(x, y);

		Rectangle rect(p1, p3);
		rect.isDamaged = damaged;

		return std::make_shared<Rectangle>(rect);
	}


	std::shared_ptr<Object> ReadFactory::greateCircle()
	{
		const int countNumbers = dataprov->rd<int>();
		bool damaged = false;

		double x = readFromData(damaged); double y = readFromData(damaged);
		Point2d p(x, y);

		double r = readFromData(damaged);

		Circle circle(p, r);
		circle.isDamaged = damaged;

		return std::make_shared<Circle>(circle);
		
	}


	std::shared_ptr<Object> ReadFactory::greateArcCircle()
	{
		const int countNumbers = dataprov->rd<int>();
		bool damaged = false;

		double x = readFromData(damaged); double y = readFromData(damaged);
		Point2d p(x, y);

		double r = readFromData(damaged);

		double startAngle = readFromData(damaged);
		double endAngle = readFromData(damaged);

		ArcCircle arc(p, r, startAngle, endAngle);
		arc.isDamaged = damaged;

		return std::make_shared<ArcCircle>(arc);
	}


	std::shared_ptr<Object> ReadFactory::greatePolygon()
	{
		const int countNumber = dataprov->rd<int>();
		bool damaged = false;

		PolyGon polygon;
		double x, y;

		for (int i = 0; i < countNumber / 2; i++) {
			x = readFromData(damaged); y = readFromData(damaged);
			polygon.addPoint(Point2d(x, y));
		}

		polygon.isDamaged = damaged;

		return std::make_shared<PolyGon>(polygon);
	}

	std::shared_ptr<Object> ReadFactory::greatePolyLine()
	{
		const int countNumber = dataprov->rd<int>();
		bool damaged = false;

		PolyLine polyline;
		double x, y;

		for (int i = 0; i < countNumber / 2; i++) {
			x = readFromData(damaged); y = readFromData(damaged);
			polyline.addPoint(Point2d(x, y));
		}

		polyline.isDamaged = damaged;

		return std::make_shared<PolyLine>(polyline);
	}


}
