#include "HttpClientPoolSingleton.h"

HttpClientPoolSingleton* HttpClientPoolSingleton::pInstance = nullptr;
std::mutex HttpClientPoolSingleton::poolMutex;

HttpClientPoolSingleton * HttpClientPoolSingleton::getInstance()
{
	if (!pInstance)
	{
		std::lock_guard<std::mutex> lock(poolMutex);
		pInstance = new HttpClientPoolSingleton();
	}
	return pInstance;
}

void HttpClientPoolSingleton::releaseInstance()
{
	std::lock_guard<std::mutex> lock(poolMutex);
	if (pInstance) {
		delete pInstance;
		pInstance = nullptr;
	}
}


