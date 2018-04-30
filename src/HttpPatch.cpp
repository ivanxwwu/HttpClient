#include "HttpPatch.h"

HttpPatch::~HttpPatch()
{
}

const char* HttpPatch::getMethodName() const
{
	return "PATCH";
}
