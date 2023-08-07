#pragma once
#include "DataProvider.h"
namespace Provider {

	template <typename T>
	class FileProvider
  	{
	public:
		FileProvider() = default;
		FileProvider(DataProvider<T>* dataprov, const std::string& patch);
		~FileProvider();

		void save();
		void read();

	private:
		DataProvider<T>* dataprov = nullptr;

	};

	template<typename T>
	inline FileProvider<T>::FileProvider(DataProvider<T>* dataprov, const std::string& patch)
	{

	}

	template<typename T>
	inline FileProvider<T>::~FileProvider()
	{
	}
	template<typename T>
	inline void FileProvider<T>::save()
	{
	}

	template<typename T>
	inline void FileProvider<T>::read()
	{
	}


}
