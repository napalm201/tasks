#pragma once
#include "Exceptions/Exception.h"
#include "Exceptions/EndOfFile.h"
#include "Exceptions/ReadError.h"
#include "Serialization.h"

#include <vector>
#include <cstdlib>
#include <fstream>
#define PI 3.141
#define THROW_ERR 23000000

namespace Provider {


    class DataProvider
    {
    public:
        DataProvider(void) = default;
        virtual ~DataProvider(void) = default;

    public:
        template <typename T>
        T rd();

        template <typename T>
        void add(T value);

        template <typename T>
        std::vector<T> rd(std::size_t size);

        template <typename T>
        void add(std::vector<T> values);

        template<typename T>
        void next(std::size_t n);

        void reset();
        void clear();

        void save(const std::string& patch);
        void read(const std::string& patch);

    private:
        std::vector<uint8_t> m_arrBytes;
        std::size_t m_nC = 0;
        Serialization::endianness m_eEndian = Serialization::endianness::big_endian;
    };

    template<typename T>
    T DataProvider::rd()
    {
        if (m_nC == m_arrBytes.size())
            throw EndOfFile();

        T primitive = Serialization::decode<T>(&m_arrBytes, m_nC);

        if (m_eEndian != Serialization::isLittle())
            primitive = Serialization::swap_bytes<T>(primitive);

        m_nC += sizeof(T);

        if (primitive == THROW_ERR)
            throw ReadError();

        return primitive;
    }



    template<typename T>
    std::vector<T> DataProvider::rd(std::size_t size)
    {
        if (m_nC + size * sizeof(T) > m_arrBytes.size()) 
            throw EndOfFile();         

        std::vector<T> values = Serialization::decode<T>(&m_arrBytes, m_nC, size);   

        if (m_eEndian != Serialization::isLittle()) 
        {
            for (T& value : values)
            {
                value = Serialization::swap_bytes<T>(value);
            }
        }

        m_nC += size * sizeof(T);

        for (T& value : values) 
            if (value == THROW_ERR)
                throw ReadError();

        return values;
    }


    template<typename T>
    inline void DataProvider::add(T value)
    {
        if (m_eEndian != Serialization::isLittle())
            value = Serialization::swap_bytes<T>(value);

        Serialization::encode(&m_arrBytes, m_arrBytes.size(), value);
    }


    template<typename T>
    void DataProvider::add(std::vector<T> values)
    {
        if (m_eEndian != Serialization::isLittle())
            for (T& value : values)
                value =  Serialization::swap_bytes<T>(value);

       Serialization::encode(&m_arrBytes, m_arrBytes.size() , values);
    }

    template<typename T>
    void DataProvider::next(std::size_t n) {
        m_nC += sizeof(T) * n;
    }
};
