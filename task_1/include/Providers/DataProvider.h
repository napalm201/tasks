#pragma once
#include "Exceptions/Exception.h"
#include "Exceptions/EndOfFile.h"
#include "Exceptions/ReadError.h"

#define PI 3.141
#define THROW_ERR 23000000

namespace Provider {

    template <typename T>
    class DataProvider
    {
    public:
        DataProvider(void) = default;
        DataProvider(T* data, std::size_t size);
        virtual ~DataProvider(void);

    public:
        template <typename U>
        U rd();

        void setdata(T* data, std::size_t size);
        void reset();

    private:
        void checkC();

    private:
        T* data = nullptr;
        std::size_t c = 0;
        std::size_t maxC = 0;

    };


    template <typename T>
    DataProvider<T>::DataProvider(T* data, std::size_t size) :  c(0), maxC(size) 
    { 
        this->data = new T[size];

        for (std::size_t i = 0; i < size; ++i)
            this->data[i] = data[i];

    }

    template<typename T>
    DataProvider<T>::~DataProvider(void)
    {
        delete[] data;
    }

    template <typename T>
    template <typename U>

    U DataProvider<T>::rd() {
        checkC();
        U d = data[c++];

        if (d == THROW_ERR)
            throw ReadError();

        return d;
    }

    template <typename T>
    void DataProvider<T>::setdata(T* data, std::size_t size) {
        c = 0;
        maxC = size;
        delete[] this->data;

        this->data = new T[size];

        for (std::size_t i = 0; i < size; ++i)
            this->data[i] = data[i];

    }

    template<typename T>
    void DataProvider<T>::reset()
    {
        c = 0;
    }

    template <typename T>
    void DataProvider<T>::checkC() {

        if (c == maxC) {
            reset();
            throw EndOfFile();
        }
    }

}; 
