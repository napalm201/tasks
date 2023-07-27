#pragma once
#include "Exceptions.h"
class DataProvider
{
public:
    DataProvider(void);
    virtual ~DataProvider(void);

public:
    virtual int rdInt();
    virtual double rdDouble();

    void setqdata() {}

    void saveqdata() {}
    void readqdata() {}

private:

    void checkC();

    int c;
    long maxC;
};
