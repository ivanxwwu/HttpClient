#ifndef IVAN_HTTPGET_H
#define IVAN_HTTPGET_H

#include "HttpRequest.h"

class HTTPCLIENT_API HttpGet : public HttpRequest {
public:
	using HttpRequest::HttpRequest;
	virtual ~HttpGet();

public:
	virtual const char* getMethodName() const;
};


#endif