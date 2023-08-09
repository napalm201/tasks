#pragma once
#include "Exceptions/Exception.h"
#include "Exceptions/EndOfFile.h"
#include "Exceptions/ReadError.h"
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
        void add(const T& prim);

        template <typename T>
        std::vector<T> rd(std::size_t size);

        template <typename T>
        void add(const std::vector<T>& array);

        void reset();
        void clear();

        void save(const std::string& patch);
        void read(const std::string& patch);

    private:
        std::vector<uint8_t> bytes;
        std::size_t c = 0;
    };

    template<typename T>
    T DataProvider::rd()
    {
        if (c == bytes.size())
            throw EndOfFile();

        T primitive;

        memcpy(&primitive, bytes.data() + c, sizeof(T));

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

        std::vector<T> data;
        data.reserve(size);

        memcpy(data.data(), bytes.data() + c, size * sizeof(T));

        for (auto dat : data) {
            if (dat == THROW_ERR)
                throw ReadError();
        }

        return data;
    }

    template<typename T>
    inline void DataProvider::add(const T& prim)
    {
        const uint8_t* d = reinterpret_cast<const uint8_t*>(&prim);

        bytes.insert(bytes.end(), d, d + sizeof(T));
        
    }

    template<typename T>
    void DataProvider::add(const std::vector<T>& array)
    {
        const uint8_t* d = reinterpret_cast<const uint8_t*>(array.data());

        std::size_t size = array.size() * sizeof(T);

        bytes.insert(bytes.end(), d, d + size);
    }


};
