#ifndef IVAN_HTTPREQUESTINFO_H
#define IVAN_HTTPREQUESTINFO_H
#include <string>
#include <map>

struct HttpRequestInfo 
{
	HttpRequestInfo() 
		:
		execTimeOut(0),
		connectTimeOut(0)
	{
	}
	HttpRequestInfo(const HttpRequestInfo& requestInfo)
		:
		execTimeOut(requestInfo.execTimeOut),
		connectTimeOut(requestInfo.connectTimeOut),
		url(requestInfo.url),
		data(requestInfo.data)
	{

	}
	double execTimeOut;
	double connectTimeOut;
	std::string url;
	std::string data;
	std::map<std::string, std::string> headers;
};

#endif