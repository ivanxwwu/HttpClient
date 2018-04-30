#ifndef IVAN_HTTPRESPONSE_H
#define IVAN_HTTPRESPONSE_H
#include "define.h"
#include <map>
#include <string>

struct HttpResponseInfo;


class HTTPCLIENT_API HttpResponse {
public:
	HttpResponse();
	HttpResponse(const HttpResponse& response);
	explicit HttpResponse(const HttpResponseInfo& info);
	virtual ~HttpResponse();
	HttpResponse(HttpResponse&& response);
	HttpResponse & operator=(HttpResponse&& response);
	HTTP_STATUS_CODE getStatusCode() const;
	void getAllHeaders(std::map<std::string, std::string>& headers) const;
	std::string getHeader(const std::string& key) const;
	std::string getData() const;
	std::string getErrMsg() const;
	double getTotalTime() const;
	int getErrCode();
	void setStatusCode(HTTP_STATUS_CODE statusCode);
	void setTotalTime(double totalTime);
	void setData(const std::string& data);
	void setErrMsg(const std::string& msg);
	void setNameLookupTime(double nameLookupTime);
	void setErrCode(int errCode);

public:
	static size_t headerCallback(char *buffer, size_t size,
		size_t nitems, void *userdata);
	void onReceiveHeader(const std::string & k, const std::string & v);
	static size_t dataCallback(void *ptr, size_t size, size_t nmemb, void *userdata);
	void onReceiveData(const std::string& data);

private:
	HttpResponseInfo* m_info;
};


#endif

