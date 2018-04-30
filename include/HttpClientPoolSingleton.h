#ifndef IVAN_HTTPCLIENTPOOLSINGLETON_H
#define IVAN_HTTPCLIENTPOOLSINGLETON_H

#include "HttpClientPool.h"
#include <mutex>

class HTTPCLIENT_API HttpClientPoolSingleton : public HttpClientPool
{
public:
	static HttpClientPoolSingleton* getInstance();
	static void releaseInstance();
private:
	static HttpClientPoolSingleton* pInstance;
	class HTTPCLIENT_API std::mutex;
	static std::mutex poolMutex;
private:
	HttpClientPoolSingleton() = default;
	HttpClientPoolSingleton(const HttpClientPoolSingleton&) = default;
};

#endif
