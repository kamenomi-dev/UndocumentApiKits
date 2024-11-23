#pragma once

#ifndef __NTDLL_INTERFACE_H__
#define __NTDLL_INTERFACE_H__

#pragma comment(lib, "ntdll.lib")

#include <Windows.h>
EXTERN_C_START

NTSYSAPI PINT_PTR NTAPI RtlGetNtVersionNumbers(UINT32* lpdwMajorVersion,
                                               UINT32* lpdwMinorVersion,
                                               UINT16* lpdwBuildNumber);

EXTERN_C_END

#endif  // !__NTDLL_INTERFACE_H__
