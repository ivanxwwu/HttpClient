#include "HttpResponse.h"
#include "HttpResponseInfo.h"
#include <iostream>
using namespace std;
HttpResponse::HttpResponse()
	:m_info(new(nothrow)  HttpResponseInfo())
{
}

HttpResponse::HttpResponse(const HttpResponse & response)
{
	m_info = new HttpResponseInfo(*response.m_info);
}

HttpResponse::HttpResponse(const HttpResponseInfo & info)
{
	m_info = new HttpResponseInfo(info);
}

HttpResponse::~HttpResponse()
{
	if (m_info) {
		delete m_info;
		m_info = nullptr;
	}
}

HttpResponse::HttpResponse(HttpResponse && response)
{
	m_info = response.m_info;
	response.m_info = nullptr;
}

HttpResponse & HttpResponse::operator=(HttpResponse && response)
{
	if (this == &response)
		return *this;
	m_info = response.m_info;
	response.m_info = nullptr;
	return *this;
}

HTTP_STATUS_CODE HttpResponse::getStatusCode() const
{
	return m_info->statusCode;
}

void HttpResponse::getAllHeaders(std::map<std::string, std::string>& headers) const
{
	headers = m_info->headers;
}

std::string HttpResponse::getHeader(const std::string & key) const
{
	return std::move(m_info->headers[key]);
}

string HttpResponse::getData() const
{
	return std::move(m_info->data);
}

std::string HttpResponse::getErrMsg() const
{
	return std::move(m_info->errMsg);
}

double HttpResponse::getTotalTime() const
{
	return m_info->totalTime;
}

int HttpResponse::getErrCode()
{
	return m_info->errCode;
}

void HttpResponse::setStatusCode(HTTP_STATUS_CODE statusCode)
{
	m_info->statusCode = statusCode;
}


void HttpResponse::setTotalTime(double totalTime)
{
	m_info->totalTime = totalTime;
}

void HttpResponse::setData(const std::string & data)
{
	m_info->data = std::move(data);
}

void HttpResponse::setErrMsg(const std::string & msg)
{
	m_info->errMsg = std::move(msg);
}

void HttpResponse::setNameLookupTime(double nameLookupTime)
{
	m_info->nameLookUpTime = nameLookupTime;
}

void HttpResponse::setErrCode(int errCode)
{
	m_info->errCode = errCode;
}

size_t HttpResponse::headerCallback(char * buffer, size_t size, size_t nitems, void * userdata)
{
	char* p = strchr(buffer, ':');
	if (!p)
		return size * nitems;
	size_t pos = p - buffer;
	HttpResponse* pUser = (HttpResponse*)userdata;
	pUser->onReceiveHeader(std::string(buffer, pos), std::string(p + 1, size*nitems - pos));
	return size * nitems;
}


void HttpResponse::onReceiveHeader(const std::string & k, const std::string & v)
{
	m_info->headers.emplace(k, v);
}

size_t HttpResponse::dataCallback(void * ptr, size_t size, size_t nmemb, void * userdata)
{
	HttpResponse* pUser = (HttpResponse*)userdata;
	pUser->onReceiveData(string((char*)ptr, size * nmemb));
	return size * nmemb;
}

void HttpResponse::onReceiveData(const std::string & data)
{
	m_info->data.append(std::move(data));
}

