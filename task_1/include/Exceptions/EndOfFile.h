#pragma once
#include "Exception.h"

class EndOfFile : public Exception
{
public:
	EndOfFile(void) = default;
	~EndOfFile(void) = default;

public:
	virtual void wait() const override;
};

