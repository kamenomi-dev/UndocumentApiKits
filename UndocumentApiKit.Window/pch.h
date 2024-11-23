/*
* General Header Defines
*/

#include <windows.h>
#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")

#include "../UndocumentApiKit.System/includes/system.info.h"

#ifndef __PCH_H__
#define __PCH_H__

typedef struct __structLoadLibraryList {
  HMODULE user32;
} LoadedLibraryList;

extern bool g_bInited;
extern bool g_bFromProcess;

extern LoadedLibraryList g_loadedList;

#ifdef UNDOCUMENTAPIKIT_WINDOW_EXPORTS
#define API_EXPORT extern "C" __declspec(dllexport)
#else
#define API_EXPORT extern "C" __declspec(dllimport)
#endif // UNDOCUMENTAPIKIT_WINDOW_EXPORTS

#endif //__PCH_H__
