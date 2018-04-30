#include "IEasyHttp.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpGet.h"
#include "HttpPost.h"
#include "HttpPatch.h"
#include "HttpPut.h"
#include "HttpDelete.h"
#include "HttpClientPoolSingleton.h"
#include "curl/curl.h"
#include <algorithm>
using namespace std;

HTTPCLIENT_API EasyResponse easyHttpGet(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers, uint32_t timeout)
{
	HttpRequest& request = HttpGet();
	request.setUrl(url);
	request.setData(body);
	for_each(headers.cbegin(), headers.cend(), [&request](auto header) {request.addHeader(header.first, header.second); });
	HttpResponse httpResponse = HttpClientPoolSingleton::getInstance()->exec(request);
	return EasyResponse{ httpResponse.getData(), httpResponse.getStatusCode() };
}

HTTPCLIENT_API EasyResponse easyHttpPost(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers, uint32_t timeout)
{
	HttpRequest& request = HttpPost();
	request.setUrl(url);
	request.setData(body);
	for_each(headers.cbegin(), headers.cend(), [&request](auto header) {request.addHeader(header.first, header.second); });
	HttpResponse httpResponse = HttpClientPoolSingleton::getInstance()->exec(request);
	return EasyResponse{ httpResponse.getData(), httpResponse.getStatusCode() };
}

HTTPCLIENT_API EasyResponse easyHttpPatch(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers, uint32_t timeout)
{
	HttpRequest& request = HttpPatch();
	request.setUrl(url);
	request.setData(body);
	for_each(headers.cbegin(), headers.cend(), [&request](auto header) {request.addHeader(header.first, header.second); });
	HttpResponse httpResponse = HttpClientPoolSingleton::getInstance()->exec(request);
	return EasyResponse{ httpResponse.getData(), httpResponse.getStatusCode() };
}

HTTPCLIENT_API EasyResponse easyHttpDelete(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers, uint32_t timeout)
{
	HttpRequest& request = HttpDelete();
	request.setUrl(url);
	request.setData(body);
	for_each(headers.cbegin(), headers.cend(), [&request](auto header) {request.addHeader(header.first, header.second); });
	HttpResponse httpResponse = HttpClientPoolSingleton::getInstance()->exec(request);
	return EasyResponse{ httpResponse.getData(), httpResponse.getStatusCode() };
}

HTTPCLIENT_API EasyResponse easyHttpPut(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers, uint32_t timeout)
{
	HttpRequest& request = HttpPut();
	request.setUrl(url);
	request.setData(body);
	for_each(headers.cbegin(), headers.cend(), [&request](auto header) {request.addHeader(header.first, header.second); });
	HttpResponse httpResponse = HttpClientPoolSingleton::getInstance()->exec(request);
	return EasyResponse{ httpResponse.getData(), httpResponse.getStatusCode() };
}

HTTPCLIENT_API string urlEncode(const std::string& is)
{
	return curl_escape(is.c_str(), is.size());
}

HTTPCLIENT_API string urlDecode(const std::string& is)
{
	return curl_unescape(is.c_str(), is.size());
}