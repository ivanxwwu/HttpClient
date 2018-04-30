#ifndef IVAN_HTTPPUT_H
#define IVAN_HTTPPUT_H

#include "HttpRequest.h"

class HTTPCLIENT_API HttpPut : public HttpRequest {
public:
	using HttpRequest::HttpRequest;
	virtual ~HttpPut();

public:
	virtual const char* getMethodName() const;
};


#endif