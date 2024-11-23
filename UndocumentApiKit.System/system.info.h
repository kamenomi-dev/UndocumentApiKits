#pragma once

#ifndef __UTILS_SYSTEM_H__
#define __UTILS_SYSTEM_H__

#include "pch.h"

#include "ntdll.interface.h"

API_EXPORT typedef struct __structVersionInformation {
  unsigned __int32 dwMajorVersion;
  unsigned __int32 dwMinorVersion;
  unsigned __int16 dwBuildNumber;
} VerInfo;

API_EXPORT BOOL KsiGetSystemVersion(_Out_ VerInfo* verInfo);
API_EXPORT BOOL KsiIsWithinVersionRange(_In_ VerInfo verBegin,
                                        _In_ VerInfo verEnd);

#endif  // !__UTILS_SYSTEM_H__
