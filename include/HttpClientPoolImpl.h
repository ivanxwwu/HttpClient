#ifndef IVAN_HTTPPOOLIMPL_H
#define IVAN_HTTPPOOLIMPL_H
#include <list>
#include <mutex>
class HttpClient;
class HttpResponse;
class HttpRequest;

class HttpClientPoolImpl
{
private:
	friend class HttpClientPool;
	HttpClientPoolImpl();
	HttpClientPoolImpl(int initNumHttp, int maxNumHttp);
	HttpResponse exec(const HttpRequest& request);
	size_t getObjNum() const;
	~HttpClientPoolImpl();

private:
	void init();
	void init(int initNumHttp, int maxNumHttp);
	void createHttpObjs();
	HttpClient* getHttpObj();
	void putHttpObj(HttpClient* pClient);
	void destroyHttpObjs();

private:
	int m_maxNumHttp;
	int m_initNumHttp;
	std::list<HttpClient*> m_listIdleHttp;
	mutable std::mutex m_mutex;
};

#endif