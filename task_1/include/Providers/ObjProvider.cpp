#include "ObjProvider.h"

namespace Provider {

	ObjProvider::ObjProvider(double* data, std::size_t size) : dataprov(data, size), readFactory(&dataprov)
	{
	}

	std::vector<std::shared_ptr<Object>> ObjProvider::getObject(bool& error)
	{
		error = false;
		std::vector<std::shared_ptr<Object>> objects;

		dataprov.reset();

		try {
			const int countObject = dataprov.rd<int>();

			for (int i = 0; i < countObject; i++) {

				const int type = dataprov.rd<int>();

				std::shared_ptr<Object> obj = readFactory.factory(type);

				if (obj == nullptr)
					readNextObject();
				else
					objects.push_back(obj);

			}
		}
		catch (const ReadError& e) {
			e.wait();
			error = true;
		}
		catch (const EndOfFile& e) {
			e.wait();
			error = true;
			objects.back()->isDamaged = true;
		}

		return objects;
	}

	void ObjProvider::setdata(double* data, std::size_t size)
	{
		dataprov.setdata(data, size);
	}

	void ObjProvider::setdata(std::vector<std::shared_ptr<Object>> objs)
	{

	}

	void ObjProvider::saveToFileData(const std::string& patch)
	{
		FileProvider<double> file(&dataprov, patch);
		file.save();
	}

	void ObjProvider::readFromFileData(const std::string& patch)
	{
		FileProvider<double> file(&dataprov, patch);
		file.read();
	}

	void ObjProvider::readNextObject()
	{
		const int counter = dataprov.rd<int>();

		double foo;

		for (int i = 0; i < counter; i++)
			foo = dataprov.rd<int>();
	}
}