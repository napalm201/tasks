#pragma once
#include <vector>
#include <memory>
#include "WDraw.h"
#include "DataProvider.h"
#include "Rect.h"
#include "ArcCircle.h"
#include "PolyLine.h"
#include "Circle.h"

class ObjProv {
public:
	ObjProv( DataProvider* dataprov) {
		ObjProv::dataprov = dataprov;
	}

	std::vector<std::shared_ptr<Object>> getObjects();

private:
    DataProvider* dataprov;
	
	class Factory {
	public:
		Factory( DataProvider* dataprov) : dataprov(dataprov) {}

		virtual std::shared_ptr<Object> factory(int type);
		
	    std::shared_ptr<Object> greateRect();
		std::shared_ptr<Object> greateCircle();
		std::shared_ptr<Object> greateArcCircle();
		std::shared_ptr<Object> greatePolygon();
		std::shared_ptr<Object> greatePolyLine();

	private:
		 DataProvider  *  dataprov;
	};
    
};


