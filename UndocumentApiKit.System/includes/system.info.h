#pragma once
#include <Windows.h>

#ifndef __INCLUDE_SYSTEM_INFO_H__
#define __INCLUDE_SYSTEM_INFO_H__

#define API_INCLUDE extern "C" __declspec(dllimport)

API_INCLUDE typedef struct __structVersionInformation {
  unsigned __int32 dwMajorVersion;
  unsigned __int32 dwMinorVersion;
  unsigned __int16 dwBuildNumber;
} VerInfo;

API_INCLUDE BOOL KsiGetSystemVersion(_Out_ VerInfo* verInfo);
API_INCLUDE BOOL KsiIsWithinVersionRange(_In_ VerInfo verBegin,
                                        _In_ VerInfo verEnd);
#endif  // !__INCLUDE_SYSTEM_INFO_H__
