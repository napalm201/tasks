#pragma once
#include <iostream>

class Exception {
public:
    Exception(void) = default;
    ~Exception(void) = default;
public:
    virtual void wait() const = 0;
};