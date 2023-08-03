#pragma once
#include "Exception.h"

class ReadError : public Exception {
public:
    ReadError(void) = default;
    ~ReadError(void) = default;
public:
    virtual void wait() const override;
};