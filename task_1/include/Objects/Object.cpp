#include "Object.h"

double Object::readFromDataProv(Provider::DataProvider* dataprov)
{
	try {
		return dataprov->rd<double>();
	}
	catch (const ReadError& e) {
		e.wait();
		isDamaged = true;
		return 0.0;
	}
	catch (const EndOfFile& e) {
		throw;
	}
}

