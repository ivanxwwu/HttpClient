#ifndef IVAN_HTTPCLIENT_H
#define IVAN_HTTPCLIENT_H

#include "define.h"

class HttpRequest;
class HttpResponse;

class HTTPCLIENT_API HttpClient {
public:
	HttpClient();
	HttpClient(const HttpClient& httpClient);
	virtual ~HttpClient();
	HttpClient(HttpClient&& httpClient);
	HttpClient& operator=(HttpClient&& httpClient);
	virtual HttpResponse exec(const HttpRequest& request);
	void enableKeepalive(bool enable, long keepIdle, long keepIntvl);
private:
	CURL* m_curl;
};

#endif
