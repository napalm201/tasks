#include "ObjProvider.h"

namespace Provider {


	ObjProvider::ObjProvider(const DataProvider& dataprov) : m_dataprov(dataprov), m_readFactory(&this->m_dataprov)
	{
	}

	std::vector<std::shared_ptr<Object>> ObjProvider::getObject()
	{

		std::vector<std::shared_ptr<Object>> objects;

		m_dataprov.reset();

		try {
			const int countObject = m_dataprov.rd<int>();

			for (int i = 0; i < countObject; ++i) {

				const int type = m_dataprov.rd<int>();

				std::shared_ptr<Object> obj = m_readFactory.factory(type);
				
				if (obj == nullptr)
					readNextObject();
				else
					objects.push_back(obj);
				
			}
		}
		catch (const ReadError& e) {
			e.wait();
		}
		catch (const EndOfFile& e) {
			e.wait();
		}
		
		return objects;
	}



	void ObjProvider::setdata(const DataProvider& dataprov)
	{
		this->m_dataprov = dataprov;
	}

	void ObjProvider::setdata(std::vector<std::shared_ptr<Object>> objs)
	{
		m_dataprov.clear();

		m_dataprov.add<int>(objs.size());

		for (auto obj : objs)
		{
			obj->pack(&m_dataprov);
		}

	}

	void ObjProvider::saveToFileData(const std::string& path)
	{
		m_dataprov.save(path);
	}

	void ObjProvider::readFromFileData(const std::string& path)
	{
		m_dataprov.read(path);
	}

	void ObjProvider::readNextObject()
	{
		const int counter = m_dataprov.rd<int>();

		m_dataprov.next<double>(counter);
	}
}