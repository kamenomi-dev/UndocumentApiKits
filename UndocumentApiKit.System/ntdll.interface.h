#pragma once

#ifndef __NTDLL_INTERFACE_H__
#define __NTDLL_INTERFACE_H__

#include <Windows.h>

#pragma comment(lib, "ntdll.lib")

EXTERN_C_START

NTSYSAPI PINT_PTR WINAPI RtlGetNtVersionNumbers(UINT32* lpdwMajorVersion,
                                                UINT32* lpdwMinorVersion,
                                                UINT16* lpdwBuildNumber);

EXTERN_C_END

#endif  // !__NTDLL_INTERFACE_H__
