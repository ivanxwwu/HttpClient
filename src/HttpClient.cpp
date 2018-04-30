#include "HttpClient.h"
#include "HttpRequestInfo.h"
#include "HttpResponseInfo.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "curl\curl.h"
#include <algorithm>
using namespace std;

HttpClient::HttpClient()
{
	curl_global_init(CURL_GLOBAL_ALL);
	m_curl = curl_easy_init();
}

HttpClient::HttpClient(const HttpClient & httpClient)
{
	curl_global_init(CURL_GLOBAL_ALL);
	m_curl = curl_easy_init();
}

HttpClient::~HttpClient()
{
	if (m_curl) {
		curl_easy_cleanup(m_curl);
	}
	curl_global_cleanup();
}

HttpClient::HttpClient(HttpClient && httpClient)
{
	m_curl = httpClient.m_curl;
	httpClient.m_curl = nullptr;
}

HttpClient & HttpClient::operator=(HttpClient && httpClient)
{
	if (this == &httpClient)
		return *this;
	m_curl = httpClient.m_curl;
	httpClient.m_curl = nullptr;
	return *this;
}

HttpResponse HttpClient::exec(const HttpRequest & request)
{
	curl_slist* headers = nullptr;
	CURLcode code;
	const map<string, string>& mapHeaders = request.getAllHeaders();
	for_each(mapHeaders.cbegin(), mapHeaders.cend(), [headers](auto header) 
			{curl_slist_append(headers, (header.first + ":" + header.second).c_str()); });
	curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(m_curl, CURLOPT_URL, request.getUrl().c_str());
	int timeoutMSeconds = int(request.getTimeOut() * 1000);
	curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, timeoutMSeconds);
	curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, request.getMethodName());
	if (!request.getData().empty()) {
		curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, request.getData().size());
		curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, request.getData().c_str());
	}
	HttpResponse response;
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, HttpResponse::dataCallback);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, HttpResponse::headerCallback);
	curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &response);
	//curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
	code = curl_easy_perform(m_curl);
	if (code != CURLE_OK) {
		response.setErrCode(code);
		response.setErrMsg(curl_easy_strerror(code));
		return std::move(response);
	}
	long retcode = 0;
	code = curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &retcode);
	if (code != CURLE_OK) {
		response.setErrCode(code);
		response.setErrMsg("response_code get fail");
		return std::move(response);
	}
	response.setStatusCode((HTTP_STATUS_CODE)retcode);
	double  totalTime = 0;
	code = curl_easy_getinfo(m_curl, CURLINFO_TOTAL_TIME, &totalTime);;
	response.setTotalTime(totalTime);
	double namelookuptime = 0;
	code = curl_easy_getinfo(m_curl, CURLINFO_NAMELOOKUP_TIME, &namelookuptime);
	response.setNameLookupTime(namelookuptime);
	return std::move(response);
}

void HttpClient::enableKeepalive(bool enable, long keepIdle, long keepIntvl)
{
	curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L ? enable : 0L);
	curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPIDLE, keepIdle ? keepIdle : 120L);
	curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPINTVL, keepIntvl ? keepIdle : 60L);
}

