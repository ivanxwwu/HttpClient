#include "HttpClientPoolImpl.h"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpResponseInfo.h"
#include <algorithm>
#include <Windows.h>


HttpClientPoolImpl::HttpClientPoolImpl()
{
	init();
}

HttpClientPoolImpl::HttpClientPoolImpl(int initNumHttp, int maxNumHttp)
{
	init(initNumHttp, maxNumHttp);
}

HttpResponse HttpClientPoolImpl::exec(const HttpRequest & request)
{
	HttpClient* pClient = nullptr;
	pClient = getHttpObj();
	if (!pClient) {
		HttpResponseInfo info;
		info.errCode = -1;
		info.errMsg = "pool get obj fail, maybe pool is empty!";
		return HttpResponse(info);
	}
	HttpResponse response = pClient->exec(request);
	putHttpObj(pClient);
	return response;
}

size_t HttpClientPoolImpl::getObjNum() const
{
	return m_listIdleHttp.size();
}

HttpClientPoolImpl::~HttpClientPoolImpl()
{
	destroyHttpObjs();
}

void HttpClientPoolImpl::init()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	m_initNumHttp = si.dwNumberOfProcessors;
	m_maxNumHttp = si.dwNumberOfProcessors * 4;
	createHttpObjs();
}

void HttpClientPoolImpl::init(int initNumHttp, int maxNumHttp)
{
	m_initNumHttp = initNumHttp;
	if (initNumHttp > maxNumHttp)
		maxNumHttp = initNumHttp;
	m_maxNumHttp = maxNumHttp;
	createHttpObjs();
}

void HttpClientPoolImpl::createHttpObjs()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	for (int i = 0; i < m_initNumHttp; i++) {
		HttpClient* pClient = new HttpClient();
		pClient->enableKeepalive(true, 300, 150);
		m_listIdleHttp.push_back(pClient);
	}
}

HttpClient * HttpClientPoolImpl::getHttpObj()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (m_listIdleHttp.empty()) {
		return nullptr;
	}
	HttpClient* pClient = m_listIdleHttp.front();
	m_listIdleHttp.pop_front();
	return pClient;
}

void HttpClientPoolImpl::putHttpObj(HttpClient * pClient)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_listIdleHttp.push_back(pClient);
}

void HttpClientPoolImpl::destroyHttpObjs()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	for_each(m_listIdleHttp.begin(), m_listIdleHttp.end(), [](auto phttp) {delete phttp; phttp = nullptr; });
	m_listIdleHttp.clear();
}

