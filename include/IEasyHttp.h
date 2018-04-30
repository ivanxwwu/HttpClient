#ifndef IVAN_IEASYHTTP_H
#define IVAN_IEASYHTTP_H

#include "HttpClient.h"
#include <map>
#include <string>

struct EasyResponse
{
	std::string data;
	HTTP_STATUS_CODE statusCode;
};

HTTPCLIENT_API EasyResponse easyHttpGet(const std::string& url, const std::string& body = std::string(), const std::map<std::string, std::string>& headers = std::map<std::string, std::string>(), uint32_t timeout = 3);
HTTPCLIENT_API EasyResponse easyHttpPost(const std::string& url, const std::string& body = std::string(), const std::map<std::string, std::string>& headers = std::map<std::string, std::string>(), uint32_t timeout = 3);
HTTPCLIENT_API EasyResponse easyHttpPatch(const std::string& url, const std::string& body = std::string(), const std::map<std::string, std::string>& headers = std::map<std::string, std::string>(), uint32_t timeout = 3);
HTTPCLIENT_API EasyResponse easyHttpDelete(const std::string& url, const std::string& body = std::string(), const std::map<std::string, std::string>& headers = std::map<std::string, std::string>(), uint32_t timeout = 3);
HTTPCLIENT_API EasyResponse easyHttpPut(const std::string& url, const std::string& body = std::string(), const std::map<std::string, std::string>& headers = std::map<std::string, std::string>(), uint32_t timeout = 3);
HTTPCLIENT_API std::string urlEncode(const std::string& is);
HTTPCLIENT_API std::string urlDecode(const std::string& is);


#endif