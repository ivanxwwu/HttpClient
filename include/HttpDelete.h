#ifndef IVAN_HTTPDELETE_H
#define IVAN_HTTPDELETE_H

#include "HttpRequest.h"

class HTTPCLIENT_API HttpDelete : public HttpRequest {
public:
	using HttpRequest::HttpRequest;
	virtual ~HttpDelete();

public:
	virtual const char*  getMethodName() const;

};


#endif