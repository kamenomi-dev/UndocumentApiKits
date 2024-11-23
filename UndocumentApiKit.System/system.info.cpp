#include "system.info.h"

API_EXPORT BOOL KsiGetSystemVersion(_Out_ VerInfo* pVerInfo) {
  VerInfo* pInfo = pVerInfo;
  // RtlZeroMemory(pInfo, sizeof VerInfo); May not to reset.

  return RtlGetNtVersionNumbers(&pInfo->dwMajorVersion, &pInfo->dwMinorVersion,
                                &pInfo->dwBuildNumber) != nullptr;
}

API_EXPORT BOOL KsiIsWithinVersionRange(_In_ UINT verBegin, _In_ UINT verEnd) {
  return BOOL();
}
