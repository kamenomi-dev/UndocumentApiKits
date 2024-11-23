#include "LibraryWindowDebugger.h"

using fnFoo = BOOL (__stdcall *)(int,int);

using std::exception;

void DebuggerBlock(HINSTANCE hInstance, int period) {
  if (period != DEBUG_PROCESS_LAUNCH) {
    return;
  }

  auto libLastStatus = GetLastError();

  HMODULE hLibrary = LoadLibraryW(L"UndocumentApiKit.Window.Debug.x64.dll");

  libLastStatus = GetLastError();
  if (libLastStatus != ERROR_SUCCESS) {
    throw new exception("Error! Your library could not be loaded! ");
  }

  /*
  * Edit you code here.
  */

  auto pFn = (fnFoo)GetProcAddress(hLibrary, "KwsSetWindowLayeredStyle");
  auto ret = pFn(263334, 2);

  FreeLibrary(hLibrary);
  hLibrary = NULL;

  cos(1);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

  static HINSTANCE hInstance{0};

  if (uMsg == WM_CREATE) {
    hInstance = *(HINSTANCE*)lParam;

    DebuggerBlock(hInstance, DEBUG_WINDOW_CREATE);
  }

  if (uMsg == WM_DESTROY) {
    PostQuitMessage(0);
  }

  return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

int APIENTRY
wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  DebuggerBlock(hInstance, DEBUG_PROCESS_LAUNCH);

  // Register class information.

  WNDCLASSEXW classInfo{0};
  classInfo.cbSize = sizeof(WNDCLASSEX);

  classInfo.style         = CS_HREDRAW | CS_VREDRAW;
  classInfo.lpfnWndProc   = WndProc;
  classInfo.hInstance     = hInstance;
  classInfo.hCursor       = LoadCursorW(nullptr, IDC_ARROW);
  classInfo.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  classInfo.lpszClassName = L"UndocumentApiKits.LibraryWindowDebugger";

  if (RegisterClassExW(&classInfo) == NULL) {
    throw new exception("Oops, it may caused something as registering class information. ");
  }

  HWND hWnd = CreateWindowExW(
      NULL,
      L"UndocumentApiKits.LibraryWindowDebugger",
      L"LibraryWindowDebugger",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      NULL,
      nullptr,
      hInstance,
      &hInstance
  );

  if (hWnd == NULL) {
    UnregisterClassW(L"UndocumentApiKits.LibraryWindowDebugger", hInstance);
    throw new exception("Oops, system prevent the current process from creating a window. ");
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  MSG msg{};
  while (GetMessageW(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  UnregisterClassW(L"UndocumentApiKits.LibraryWindowDebugger", hInstance);
  return (int)msg.wParam;
}