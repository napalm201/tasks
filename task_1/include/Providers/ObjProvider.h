#pragma once


#include "Objects/Figures.h"
#include "DataProvider.h"
#include "ReadFactory.h"
#include "FileProvider.h"

namespace Provider {

    class ObjProvider
    {
    public:
        ObjProvider(void) = default;
        ObjProvider(const DataProvider& dataprov);
        virtual ~ObjProvider(void) = default;

    public:
        virtual std::vector<std::shared_ptr<Object>> getObject();

        void setdata(const DataProvider& dataprov);
        void setdata(std::vector<std::shared_ptr<Object>> objs);

        template <typename T>
        void setdata(T* data, std::size_t size);

        void saveToFileData(const std::string& patch);
        void readFromFileData(const std::string& patch);
                
    private:
        virtual void readNextObject();

    private:
        ReadFactory readFactory = ReadFactory(&this->dataprov);
        DataProvider dataprov;
    };

    template<typename T>
    void ObjProvider::setdata(T* data, std::size_t size)
    {
        dataprov.clear();

        int base = 0;
        const int countObj = data[base++];
        dataprov.add<int>(countObj);

        for (int j = 0; j < countObj; j++) {

            const int type = data[base++];
            const int countData = data[base++];
            dataprov.add<int>(type); dataprov.add<int>(countData);

            for (int j = 0; j < countData; j++) {

                const double value = data[base++];
                dataprov.add<double>(value);

            }

        }
    }


}