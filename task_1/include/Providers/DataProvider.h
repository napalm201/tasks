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
    inline void DataProvider::add(const T& prim)
    {
        const uint8_t* d = reinterpret_cast<const uint8_t*>(&prim);

        bytes.insert(bytes.end(), d, d + sizeof(T));
        
    }


};
