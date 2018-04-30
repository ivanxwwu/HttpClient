#include "HttpRequest.h"
#include "HttpRequestInfo.h"
using namespace std;

HttpRequest::HttpRequest()
	:m_info(new(nothrow) HttpRequestInfo())
{
}

HttpRequest::HttpRequest(const std::string & uri, double timeout)
{
	m_info = new HttpRequestInfo();
	m_info->url = uri;
	m_info->execTimeOut = timeout;
}

HttpRequest::HttpRequest(const HttpRequest & request)
	: m_info(new HttpRequestInfo(*request.m_info))
{
}

HttpRequest::~HttpRequest()
{
	if (m_info)
	{
		delete m_info;
		m_info = nullptr;
	}
}

HttpRequest::HttpRequest(HttpRequest && request)
{
	m_info = request.m_info;
	request.m_info = nullptr;
}

HttpRequest & HttpRequest::operator=(HttpRequest && request)
{
	if (this == &request)
		return *this;
	m_info = request.m_info;
	request.m_info = nullptr;
	return *this;
}

void HttpRequest::addHeader(const std::string & key, const std::string & value)
{
	m_info->headers.emplace(key, value);
}

void HttpRequest::setUrl(const std::string & url)
{
	m_info->url = url;
}

void HttpRequest::setData(const std::string & data)
{
	m_info->data = std::move(data);
}

void HttpRequest::setTimeOut(double timeout)
{	
	m_info->execTimeOut = timeout;
}

const std::map<std::string, std::string>& HttpRequest::getAllHeaders() const
{
	return m_info->headers;
}

const std::string & HttpRequest::getHeader(const std::string & key) const
{
	return m_info->headers[key];
}

const std::string & HttpRequest::getUrl() const
{
	return m_info->url;
}

const std::string & HttpRequest::getData() const
{
	return m_info->data;
}

double HttpRequest::getTimeOut() const
{
	return m_info->execTimeOut;
}
