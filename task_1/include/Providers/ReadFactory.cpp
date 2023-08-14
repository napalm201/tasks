#include "ReadFactory.h"

namespace Provider {

	ReadFactory::ReadFactory(DataProvider* dataprov) : m_pDataprov(dataprov)
	{

	}

	std::shared_ptr<Object> ReadFactory::factory(const int type)
	{
		try {

			switch (type) {
			case 1:
				return getRect();
			case 2:
				return getCircle();
			case 4:
				return getArcCircle();
			case 5:
				return getPolygon();
			case 6:
				return getPolyLine();
			default:
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


	std::shared_ptr<Object> ReadFactory::getRect()
	{
		std::shared_ptr<Object> rect = std::make_shared<Rectangle>();
		rect->unpack(m_pDataprov);

		return rect;
	}


	std::shared_ptr<Object> ReadFactory::getCircle()
	{
		std::shared_ptr<Object> circle = std::make_shared<Circle>();
		circle->unpack(m_pDataprov);

		return circle;
	}


	std::shared_ptr<Object> ReadFactory::getArcCircle()
	{
		std::shared_ptr<Object> arc = std::make_shared<ArcCircle>();
		arc->unpack(m_pDataprov);

		return arc;
	}


	std::shared_ptr<Object> ReadFactory::getPolygon()
	{
		std::shared_ptr<Object> polygon = std::make_shared<PolyGon>();
     	polygon->unpack(m_pDataprov);

		return polygon;
	}

	std::shared_ptr<Object> ReadFactory::getPolyLine()
	{
		std::shared_ptr<Object> polyline = std::make_shared<PolyLine>();
		polyline->unpack(m_pDataprov);

		return polyline;
	}


}
