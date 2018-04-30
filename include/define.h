#ifndef IVAN_DEFINE_H
#define IVAN_DEFINE_H

#include <stdint.h>

#if defined(WIN32) || defined(_WIN32) 
#ifdef LIB_HTTPCLIENT_LIBRARY
#define HTTPCLIENT_API __declspec(dllexport)
#else
#define HTTPCLIENT_API __declspec(dllimport)
#endif
#endif  //END SYSTEM

using CURL = void;
using HTTP_STATUS_CODE = uint16_t;

//proxy   auth
#endif