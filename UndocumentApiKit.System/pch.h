
#ifndef __PCH_H__
#define __PCH_H__

#include <windows.h>

#ifdef UNDOCUMENTAPIKIT_SYSTEM_EXPORTS
#define API_EXPORT extern "C" __declspec(dllexport)
#else
#define API_EXPORT extern "C" __declspec(dllimport)
#endif  // UNDOCUMENTAPIKIT_SYSTEM_EXPORTS

#endif //__PCH_H__
