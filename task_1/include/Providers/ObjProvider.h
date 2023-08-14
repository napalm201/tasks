#pragma once
#include "Objects/Figures.h"
#include "DataProvider.h"
#include "ReadFactory.h"


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

        void saveToFileData(const std::string& path);
        void readFromFileData(const std::string& path);
                
    private:
        virtual void readNextObject();

    private:
        ReadFactory m_readFactory = ReadFactory(&this->m_dataprov);
        DataProvider m_dataprov;
    };

    template<typename T>
    void ObjProvider::setdata(T* data, std::size_t size)
    {
        m_dataprov.clear();

        int base = 0;
        const int countObj = data[base++];

        m_dataprov.add<int>(countObj);

        for (int j = 0; j < countObj; j++) {

            const int type = data[base++];
            const int countData = data[base++];

            m_dataprov.add<int>(type); m_dataprov.add<int>(countData);

            for (int j = 0; j < countData; j++) {

                const double value = data[base++];
                m_dataprov.add<double>(value);

            }

        }
    }


}