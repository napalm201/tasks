#pragma once


#include "Objects/Figures.h"
#include "DataProvider.h"
#include "ReadFactory.h"

namespace Provider {

    class ObjProvider
    {
    public:
        ObjProvider(void) = default;
        ObjProvider(double* data, std::size_t size);
        virtual ~ObjProvider(void) = default;

    public:
        virtual std::vector<std::shared_ptr<Object>> getObject();

        void setdata(double* data, std::size_t);
        void setdata(std::vector<std::shared_ptr<Object>> objs);

        void saveToFileData(const std::string& patch);
        void readFromFileData(const std::string& patch);

    private:
        virtual void readNextObject();

    private:
        ReadFactory readFactory;
        DataProvider<double> dataprov;
    };

}