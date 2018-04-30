#include "HttpPost.h"

HttpPost::~HttpPost()
{
}

const char* HttpPost::getMethodName() const
{
	return "POST";
}
