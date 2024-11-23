#include "pch.h"

typedef struct __structLoadLibraryList {
  HMODULE NtDLL;
} LoadedLibraryList;

extern bool g_bInited{false};
extern bool g_bFromProcess{false};

extern LoadedLibraryList g_bLoadedList{};

#include "system.info.h"

API_EXPORT BOOL KsInitializeLibrary(_In_ bool bFromProcess);
API_EXPORT BOOL KsUninitializeLibrary(_In_ bool bFromProcess);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall,
                      LPVOID lpReserved) {
  switch (ulReasonForCall) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
      KsInitializeLibrary(ulReasonForCall == DLL_PROCESS_ATTACH);
      break;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      KsUninitializeLibrary(ulReasonForCall == DLL_PROCESS_DETACH);
      break;
  }
  return TRUE;
}

static void FreeAllExistLoadedLibrary() {
  if (g_bLoadedList.NtDLL != nullptr) {
    FreeLibrary(g_bLoadedList.NtDLL);
    g_bLoadedList.NtDLL = nullptr;
  }
};

API_EXPORT BOOL KsInitializeLibrary(_In_ bool bFromProcess) {
  g_bFromProcess = bFromProcess;

  auto hLibrary = LoadLibraryW(L"ntdll.dll");
  if (hLibrary == nullptr) {
    return g_bInited = false;
  }

  g_bLoadedList.NtDLL = hLibrary;

  return g_bInited = true;
}

API_EXPORT BOOL KsUninitializeLibrary(_In_ bool bFromProcess) {
  if (g_bFromProcess != bFromProcess) {
    SetLastError(ERROR_INVALID_DATA);
  }

  FreeAllExistLoadedLibrary();

  return true;
}