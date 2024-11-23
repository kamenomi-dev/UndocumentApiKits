/*
* General Header Defines
*/

#ifndef __PCH_H__
#define __PCH_H__

#include <windows.h>

#ifdef UNDOCUMENTAPIKITWINDOW_EXPORTS
#define API_EXPORT extern "C" __declspec(dllexport)
#else
#define API_EXPORT extern "C" __declspec(dllimport)
#endif // UNDOCUMENTAPIKITWINDOW_EXPORTS

#endif //__PCH_H__
