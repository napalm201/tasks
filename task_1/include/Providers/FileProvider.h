#pragma once
#include "DataProvider.h"
namespace Provider {

	template <typename T>
	class FileProvider
  	{
	public:
		FileProvider(DataProvider<T>* dataprov, const std::string& patch);
		~FileProvider();

		void save();
		void read();

	private:
		DataProvider<T>* dataprov = nullptr;
	};

}
