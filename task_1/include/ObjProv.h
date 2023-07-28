#pragma once
#include <vector>
#include <memory>
#include "WDraw.h"
#include "DataProvider.h"
#include "Rect.h"
#include "ArcCircle.h"
#include "PolyGon.h"
#include "PolyLine.h"
#include "Circle.h"
#include <unordered_set>

class ObjProv {
public:
	ObjProv(DataProvider* dataprov);

	std::vector<std::shared_ptr<Object>> getObjects();

private:
	void readNextObject();

private:
    DataProvider * dataprov;
	

	class ReadFactory {
	public:
		ReadFactory(DataProvider* dataprov);

		virtual std::shared_ptr<Object> factory(int type);
		double readFromData();

	    std::shared_ptr<Object> greateRect();
		std::shared_ptr<Object> greateCircle();
		std::shared_ptr<Object> greateArcCircle();
		std::shared_ptr<Object> greatePolygon();
		std::shared_ptr<Object> greatePolyLine();

	private:
		 DataProvider  *  dataprov;
	};
    
};


