#ifndef IVAN_HTTPRESPONSEINFO_H
#define IVAN_HTTPRESPONSEINFO_H

#include "define.h"
#include <stdint.h>
#include <string>
#include <map>

struct HttpResponseInfo
{
	HttpResponseInfo() 
		:
		statusCode(0),
		nameLookUpTime(0),
		connectTime(0),
		totalTime(0),
		localPort(0),
		remotePort(0),
		requestSize(0),
		headerSize(0),
		errCode(0)
	{

	}
	HttpResponseInfo(const HttpResponseInfo& responseInfo) 
		:
		statusCode(responseInfo.statusCode),
		nameLookUpTime(responseInfo.nameLookUpTime),
		connectTime(responseInfo.connectTime),
		totalTime(responseInfo.totalTime),
		localPort(responseInfo.localPort),
		remotePort(responseInfo.remotePort),
		requestSize(responseInfo.requestSize),
		headerSize(responseInfo.headerSize),
		http_version(responseInfo.http_version),
		localIp(responseInfo.localIp),
		remoteIp(responseInfo.remoteIp)
	{

	}
	std::string http_version;
	HTTP_STATUS_CODE statusCode;
	double nameLookUpTime;
	double connectTime;
	double totalTime;
	std::string localIp;
	uint16_t localPort;
	std::string remoteIp;
	uint16_t remotePort;
	uint32_t requestSize;
	uint32_t headerSize;
	std::string data;
	std::map<std::string, std::string> headers;
	std::string errMsg;
	uint32_t errCode;
	//std::string redirectUrl;
	//uint32_t protocol;
};

#endif