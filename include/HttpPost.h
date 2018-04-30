#ifndef IVAN_HTTPPOST_H
#define IVAN_HTTPPOST_H

#include "HttpRequest.h"

class HTTPCLIENT_API HttpPost : public HttpRequest {
public:
	using HttpRequest::HttpRequest;
	virtual ~HttpPost();

public: 
	virtual const char* getMethodName() const;
};


#endif