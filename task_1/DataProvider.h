#pragma once

class DataProvider
{
public:
    DataProvider(void);
    virtual ~DataProvider(void);

    virtual int rdInt();
    virtual double rdDouble();

private:

    void checkC();

    int c;
    long maxC;
};
