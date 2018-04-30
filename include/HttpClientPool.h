#ifndef IVAN_HTTPPOOL_H
#define IVAN_HTTPPOOL_H
#include "define.h"
#include <list>
#include <mutex>
class HttpClient;
class HttpRequest;
class HttpResponse;
class HttpClientPoolImpl;

class HTTPCLIENT_API HttpClientPool
{
public:
	HttpClientPool();
	HttpClientPool(int initNumHttp, int maxNumHttp);
	HttpResponse exec(const HttpRequest& request);
	size_t getObjNum() const;
	~HttpClientPool();

private:
	void init();
	void init(int initNumHttp, int maxNumHttp);
	void createHttpObjs();
	HttpClient* getHttpObj();
	void putHttpObj(HttpClient* pClient);

private:
	HttpClientPoolImpl * m_impl;
};

#endif
