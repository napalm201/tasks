#pragma once
#include "DataProvider.h"
#include <fstream>
#include <vector>

namespace Provider {

	template <typename T>
	class FileProvider
  	{
	public:
		FileProvider() = default;
		FileProvider(DataProvider<T>* dataprov, const std::string& patch);
		virtual ~FileProvider();

	public:
		void save();
		void read();

	private:
		DataProvider<T>* dataprov = nullptr;
		std::string patch;
	};

	template<typename T>
	FileProvider<T>::FileProvider(DataProvider<T>* dataprov, const std::string& patch) : dataprov(dataprov), patch(patch)
	{

	}

	template<typename T>
	FileProvider<T>::~FileProvider()
	{
	}

	template<typename T>
    void FileProvider<T>::save()
	{

		std::ofstream file(patch, std::ios::binary);
		dataprov->reset();

		try {

			const int countObj = dataprov->rd<int>();
			file.write(reinterpret_cast<const char*>(&countObj), sizeof(int));

			for (int i = 0; i < countObj; i++) {
				
				const int type = dataprov->rd<int>(); 
				const int countData = dataprov->rd<int>();
				
				file.write(reinterpret_cast<const char*>(&type), sizeof(int));
				file.write(reinterpret_cast<const char*>(&countData), sizeof(int));
				
				for (int j = 0; j < countData; j++) {

					T data = dataprov->rd<T>();
					file.write(reinterpret_cast<const char*>(&data), sizeof(T));

				}
					

			}

		}
		catch (const std::ios_base::failure& ex) {
			std::cout << ex.what();
		}
		catch (const ReadError& e) {
			e.wait();
		}
		catch (const EndOfFile& e) {
			e.wait();
		}

	}

	template<typename T>
    void FileProvider<T>::read()
	{
			std::ifstream file(patch, std::ios::binary);
			std::vector<T> data;

			try {

				int countObj;
				file.read(reinterpret_cast<char*>(&countObj), sizeof(int));
				data.push_back((T)countObj);

				for (int i = 0; i < countObj; i++) {

					int type, countData;
					file.read(reinterpret_cast<char*>(&type), sizeof(int));
					file.read(reinterpret_cast<char*>(&countData), sizeof(int));

					data.push_back((T)type);
					data.push_back((T)countData);

					for (int j = 0; j < countData; j++) {

						T cordinate;
						file.read(reinterpret_cast<char*>(&cordinate), sizeof(T));
						data.push_back(cordinate);

					}
 
				}

				dataprov->setdata(data.data(), data.size());

			}
			catch (const std::ios_base::failure& ex) {
				std::cout << ex.what();
			}
		

	}


}
