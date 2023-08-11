#include "ObjProvider.h"

namespace Provider {


	ObjProvider::ObjProvider(const DataProvider& dataprov) : dataprov(dataprov), readFactory(&this->dataprov)
	{
	}

	std::vector<std::shared_ptr<Object>> ObjProvider::getObject()
	{

		std::vector<std::shared_ptr<Object>> objects;

		dataprov.reset();

		try {
			const int countObject = dataprov.rd<int>();

			for (int i = 0; i < countObject; i++) {

				const int type = dataprov.rd<int>();

				std::shared_ptr<Object> obj = readFactory.factory(type);
				
				if (obj == nullptr)
					readNextObject();
				else {
					objects.push_back(obj);
				}
				
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
		this->dataprov = dataprov;
	}

	void ObjProvider::setdata(std::vector<std::shared_ptr<Object>> objs)
	{
		dataprov.clear();

		for (auto obj : objs)
		{
			obj->pack(&dataprov);
		}

	}

	void ObjProvider::saveToFileData(const std::string& patch)
	{
		dataprov.save(patch);
	}

	void ObjProvider::readFromFileData(const std::string& patch)
	{
		dataprov.read(patch);
	}

	void ObjProvider::readNextObject()
	{
		const int counter = dataprov.rd<int>();

		dataprov.next<double>(counter);
	}
}