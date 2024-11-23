#include "pch.h"

extern bool g_bInited{false};
extern bool g_bFromProcess{false};

extern LoadedLibraryList g_loadedList{};

#include "window.style.h"

API_EXPORT BOOL KwInitializeLibrary(_In_ bool bFromProcess);
API_EXPORT BOOL KwUninitializeLibrary(_In_ bool bFromProcess);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved) {
  switch (ulReasonForCall) {
  case DLL_PROCESS_ATTACH:
  case DLL_THREAD_ATTACH:
    KwInitializeLibrary(ulReasonForCall == DLL_PROCESS_ATTACH);
    break;
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    KwUninitializeLibrary(ulReasonForCall == DLL_PROCESS_DETACH);
    break;
  }
  return TRUE;
}

API_EXPORT BOOL KwInitializeLibrary(_In_ bool bFromProcess) {
  g_bFromProcess = bFromProcess;

  auto hLibrary = LoadLibraryW(L"user32.dll");
  if (hLibrary == nullptr) {
    return g_bInited = false;
  }

  g_loadedList.user32 = hLibrary;

  if (!KwsInitialize()) {
    KwUninitializeLibrary(bFromProcess);
    g_bInited = false;
  }

  return g_bInited = true;
}

static void FreeAllExistLoadedLibrary() {
  if (g_loadedList.user32 != nullptr) {
    FreeLibrary(g_loadedList.user32);
    g_loadedList.user32 = nullptr;
  }
};

API_EXPORT BOOL KwUninitializeLibrary(_In_ bool bFromProcess) {
  if (g_bFromProcess != bFromProcess) {
    SetLastError(ERROR_INVALID_DATA);
  }

  if (KwsUninitialize()) {
    SetLastError(ERROR_INVALID_FUNCTION);
  }
  FreeAllExistLoadedLibrary();

  g_bInited = false;
  return true;
}