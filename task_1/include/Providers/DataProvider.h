#pragma once
#include "Exceptions/Exception.h"
#include "Exceptions/EndOfFile.h"
#include "Exceptions/ReadError.h"
#include "Serialization.h"

#include <vector>
#include <cstdlib>
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
        void add(const std::vector<T>& values);

        template<typename T>
        void next(std::size_t n);

        void reset();
        void clear();

        void save(const std::string& patch);
        void read(const std::string& patch);

    private:
        std::vector<uint8_t> bytes;
        std::size_t c = 0;
        Serialization::endianness endian = Serialization::endianness::little_endian;
    };

    template<typename T>
    T DataProvider::rd()
    {
        if (c == bytes.size())
            throw EndOfFile();

        T primitive = Serialization::decode<T>(&bytes, c);


        if (endian != Serialization::isLittle())
            primitive = Serialization::swap_bytes<T>(primitive);

        c += sizeof(T);

        if (primitive == THROW_ERR)
            throw ReadError();

        return primitive;
    }



    template<typename T>
    std::vector<T> DataProvider::rd(std::size_t size)
    {
        if (c + size * sizeof(T) > bytes.size()) 
            throw EndOfFile();         

        std::vector<T> values = Serialization::decode<T>(&bytes, c, size);   

        if (endian != Serialization::isLittle()) {
            for (T& value : values) {
                value = Serialization::swap_bytes<T>(value);
            }
        }

        c += size * sizeof(T);

        for (T& value : values) 
            if (value = THROW_ERR)
                throw ReadError();

        return values;
    }


    template<typename T>
    inline void DataProvider::add( T value)
    {
        if (endian != Serialization::isLittle())
            value = Serialization::swap_bytes<T>(value);

        Serialization::encode(&bytes, value);
    }


    template<typename T>
    void DataProvider::add(const std::vector<T>& values)
    {
        if (endian != Serialization::isLittle())
            for (const T& value : values)
                add<T>(value);
        else
            Serialization::encode(&bytes, values);
    }

    template<typename T>
    void DataProvider::next(std::size_t n) {
        c += sizeof(T) * n;
    }
};
