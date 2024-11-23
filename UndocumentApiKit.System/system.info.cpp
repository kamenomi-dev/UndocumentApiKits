#include "system.info.h"

API_EXPORT BOOL KsiGetSystemVersion(_Out_ VerInfo* pVerInfo) {
  VerInfo* pInfo = pVerInfo;
  // RtlZeroMemory(pInfo, sizeof VerInfo); May not to reset.

  return RtlGetNtVersionNumbers(&pInfo->dwMajorVersion, &pInfo->dwMinorVersion,
                                &pInfo->dwBuildNumber) != nullptr;
}

API_EXPORT BOOL KsiIsWithinVersionRange(_In_ VerInfo verLeft,
                                        _In_ VerInfo verRight) {
  VerInfo currVerInfo{};
  if (KsiGetSystemVersion(&currVerInfo) == FALSE) {
    return FALSE;
  }

  if (verLeft.dwMajorVersion != NULL &&
      currVerInfo.dwMajorVersion < verLeft.dwMajorVersion) {
    return FALSE;
  }

  if (verRight.dwMajorVersion != NULL &&
      verRight.dwMajorVersion < currVerInfo.dwMajorVersion) {
    return FALSE;
  }

  if (verLeft.dwMinorVersion != NULL &&
      currVerInfo.dwMinorVersion < verLeft.dwMinorVersion) {
    return FALSE;
  }

  if (verRight.dwMinorVersion != NULL &&
      verRight.dwMinorVersion < currVerInfo.dwMinorVersion) {
    return FALSE;
  }

  if (verLeft.dwBuildNumber != NULL &&
      currVerInfo.dwBuildNumber < verLeft.dwBuildNumber) {
    return FALSE;
  }

  if (verRight.dwBuildNumber != NULL &&
      verRight.dwBuildNumber < currVerInfo.dwBuildNumber) {
    return FALSE;
  }

  return TRUE;
}
