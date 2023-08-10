#include "ReadFactory.h"

namespace Provider {

	ReadFactory::ReadFactory(DataProvider* dataprov) : dataprov(dataprov)
	{

	}

	std::shared_ptr<Object> ReadFactory::factory(const int type)
	{
		try {
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
		catch (const EndOfFile& e) {
			throw e;
		}
		catch (const ReadError& e) {
			throw e;
		}
	}


	std::shared_ptr<Object> ReadFactory::greateRect()
	{
		std::shared_ptr<Object> rect = std::make_shared<Rectangle>();
		rect->unpack(dataprov);

		return rect;
	}


	std::shared_ptr<Object> ReadFactory::greateCircle()
	{
		std::shared_ptr<Object> circle = std::make_shared<Circle>();
		circle->unpack(dataprov);

		return circle;
	}


	std::shared_ptr<Object> ReadFactory::greateArcCircle()
	{
		std::shared_ptr<Object> arc = std::make_shared<ArcCircle>();
		arc->unpack(dataprov);

		return arc;
	}


	std::shared_ptr<Object> ReadFactory::greatePolygon()
	{
		std::shared_ptr<Object> polygon = std::make_shared<PolyGon>();
     	polygon->unpack(dataprov);

		return polygon;
	}

	std::shared_ptr<Object> ReadFactory::greatePolyLine()
	{
		std::shared_ptr<Object> polyline = std::make_shared<PolyLine>();
		polyline->unpack(dataprov);

		return polyline;
	}


}
