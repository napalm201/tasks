#pragma once
#include <iostream>

class Exceptions {
public:
    virtual void wait() const = 0;
};

class EndOfFile : public Exceptions
{
public:
    EndOfFile(void);
    ~EndOfFile(void);
    virtual void wait() const {};
};

class ReadError : public Exceptions{
public:
    ReadError(void);
    ~ReadError(void);
    virtual void wait() const {};

};

class UnderfindObj : public Exceptions {
public:
    UnderfindObj(void);
    ~UnderfindObj(void);
    virtual void wait() const {};
 
};