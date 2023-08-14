#pragma once
#include "Objects/Figures.h"
#include "DataProvider.h"

namespace Provider {

	class ReadFactory {
	private:
		ReadFactory(void) = default;
		ReadFactory(DataProvider* dataprov);
		virtual ~ReadFactory(void) = default;

		friend class ObjProvider;

	public:
		virtual std::shared_ptr<Object> factory(const int type);

		std::shared_ptr<Object> getRect();
		std::shared_ptr<Object> getCircle();
		std::shared_ptr<Object> getArcCircle();
		std::shared_ptr<Object> getPolygon();
		std::shared_ptr<Object> getPolyLine();

	private:
		DataProvider* m_pDataprov = nullptr;
	};


};