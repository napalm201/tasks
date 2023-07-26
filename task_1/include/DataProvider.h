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



public:


private:

    void checkC();

    int c;
    long maxC;
};
