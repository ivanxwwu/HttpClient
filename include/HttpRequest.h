#ifndef IVAN_HTTPREQUEST_H
#define IVAN_HTTPREQUEST_H

#include "define.h"
#include <map>
#include <string>

struct HttpRequestInfo;

class HTTPCLIENT_API HttpRequest {
public:
	virtual const char* getMethodName() const = 0;

public:
	HttpRequest();
	HttpRequest(const std::string& uri, double timeout = 5.0);
	HttpRequest(const HttpRequest& request);
	virtual ~HttpRequest();
	HttpRequest(HttpRequest&& request);
	HttpRequest& operator=(HttpRequest&& request);
	void addHeader(const std::string& key, const std::string& value);
	void setUrl(const std::string& url);
	void setData(const std::string& body);
	void setTimeOut(double timeout);
	const std::map<std::string, std::string>& getAllHeaders() const;
	const std::string& getHeader(const std::string& key) const;
	const std::string& getUrl() const;
	const std::string& getData() const;
	double getTimeOut() const;

protected:
	HttpRequestInfo* m_info;
};


#endif