#ifndef IVAN_HTTPPATCH_H
#define IVAN_HTTPPATCH_H

#include "HttpRequest.h"

class HTTPCLIENT_API HttpPatch : public HttpRequest {
public:
	using HttpRequest::HttpRequest;
	virtual ~HttpPatch();

public:
	virtual const char* getMethodName() const;
};


#endif