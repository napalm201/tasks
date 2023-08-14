#include "Object.h"

bool Object::isDamaged() const
{
	return m_bDamaged;
}

double Object::readFromDataProv(Provider::DataProvider* dataprov)
{
	try {
		return dataprov->rd<double>();
	}
	catch (const ReadError& e) {
		e.wait();
		m_bDamaged = true;
		return 0.0;
	}
	catch (const EndOfFile& e) {
		throw e;
	}
}

