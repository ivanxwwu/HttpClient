# HttpClient

基于libcurl的http简易客户端，带连接池,目前版本应用在windows下,文档持续更新，疑问咨询QQ23449470

# sample1
```cpp
#include <iostream>
#include "HttpClient.h"
#include "HttpPost.h"
#include "HttpResponse.h"
using namespace std;
#ifdef _DEBUG
#pragma comment(lib, "HttpClientD.lib")
#else
#pragma comment(lib, "HttpCLient.lib")
#endif

int main()
{
	HttpClient client;
	HttpRequest& request = HttpPost("http://www.baidu.com", 3);
	HttpResponse response = client.exec(request);
	printf("%d\n", response.getStatusCode());
	printf("%s\n", response.getData());
}
```
