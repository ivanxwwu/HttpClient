#include "HttpClientPool.h"
#include "HttpClientPoolImpl.h"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpResponseInfo.h"
#include <Windows.h>

HttpClientPool::HttpClientPool()
	:m_impl(new HttpClientPoolImpl())
{
	
}

HttpClientPool::HttpClientPool(int initNumHttp, int maxNumHttp)
	:m_impl(new HttpClientPoolImpl(initNumHttp, maxNumHttp))
{
}

HttpResponse HttpClientPool::exec(const HttpRequest & request)
{
	return m_impl->exec(request);
}

size_t HttpClientPool::getObjNum() const
{
	return m_impl->getObjNum();
}

HttpClientPool::~HttpClientPool()
{
	if (m_impl) {
		delete m_impl;
		m_impl = nullptr;
	}
}

void HttpClientPool::init()
{
	m_impl->init();
}

void HttpClientPool::init(int initNumHttp, int maxNumHttp)
{
	m_impl->init(initNumHttp, maxNumHttp);
}

void HttpClientPool::createHttpObjs()
{
	m_impl->createHttpObjs();
}

HttpClient * HttpClientPool::getHttpObj()
{
	return m_impl->getHttpObj();
}

void HttpClientPool::putHttpObj(HttpClient * pClient)
{
	m_impl->putHttpObj(pClient);
}
