#include "window.style.h"

static fnSetWindowCompositionAttributeType* g_fnSetWindowCompositionAttribute;
static fnGetWindowCompositionAttributeType* g_fnGetWindowCompositionAttribute;

BOOL __stdcall KwsInitialize() {
  if (g_loadedList.user32 == NULL) {
    SetLastError(ERROR_NOT_READY);
    return FALSE;
  }

  g_fnSetWindowCompositionAttribute =
      (fnSetWindowCompositionAttributeType*)GetProcAddress(g_loadedList.user32, "SetWindowCompositionAttribute");
  g_fnGetWindowCompositionAttribute =
      (fnGetWindowCompositionAttributeType*)GetProcAddress(g_loadedList.user32, "GetWindowCompositionAttribute");

  SetLastError(0); // it could work?
  return TRUE;
}

BOOL __stdcall KwsUninitialize() {
  g_fnSetWindowCompositionAttribute = NULL;
  g_fnGetWindowCompositionAttribute = NULL;
  return TRUE;
}

API_EXPORT BOOL KwsApplyWindowLayeredMica(HWND hWnd, bool bEnable) {
  VerInfo verInfo{};
  KsiGetSystemVersion(&verInfo);

  const auto buildVersion = verInfo.dwBuildNumber;
  if (buildVersion < 22000) {
    return FALSE;
  }

  if (buildVersion < 22523) {
    return DwmSetWindowAttribute(hWnd, DWMWA_MICA_EFFECT, &bEnable, sizeof bEnable) == S_OK;
  }

  auto value = bEnable ? User32Defines::SystemBackdropType::Mica : User32Defines::SystemBackdropType::None;
  return DwmSetWindowAttribute(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &value, sizeof value);
}

API_EXPORT BOOL KwsSetWindowLayeredStyle(_In_ HWND hWnd, _In_ LayeredStyle style) {
  static LayeredStyle lastStyle = LayeredStyle::None;

  if (!IsWindow(hWnd)) {
    return FALSE;
  }

  if (style == lastStyle) {
    return TRUE;
  }

  if (lastStyle == LayeredStyle::Mica) {
    KwsApplyWindowLayeredMica(hWnd, false);
  }

  lastStyle = style;

  if (style == LayeredStyle::Mica) {
    return KwsApplyWindowLayeredMica(hWnd, true);
  }

  if (KsiIsWithinVersionRange({6, 0, 0}, {6, 1, 0})) {
    DWM_BLURBEHIND blurBehind{};
    blurBehind.dwFlags  = DWM_BB_ENABLE;
    blurBehind.fEnable  = true;
    blurBehind.hRgnBlur = NULL;
    return DwmEnableBlurBehindWindow(hWnd, &blurBehind) == S_OK;
  }

  User32Defines::AccentPolicy                   accentPolicy{};
  User32Defines::WindowCompositionAttributeData windowAttrData{};
  windowAttrData.Attrib = User32Defines::WindowCompositionAttribute::WCA_ACCENT_POLICY;
  windowAttrData.cbData = sizeof(accentPolicy);
  windowAttrData.pvData = &accentPolicy;

  switch (style) {
  case LayeredStyle::Aero:
    accentPolicy.AccentState = User32Defines::AccentState::ACCENT_ENABLE_BLURBEHIND;
    break;
  case LayeredStyle::Acrylic:
    accentPolicy.AccentState = User32Defines::AccentState::ACCENT_ENABLE_ACRYLICBLURBEHIND;
    break;
  default:
    accentPolicy.AccentState = User32Defines::AccentState::ACCENT_DISABLED;
    break;
  }

  return (*g_fnSetWindowCompositionAttribute)(hWnd, &windowAttrData);
}

API_EXPORT BOOL KwsGetWindowLayeredStyle(_In_ HWND hWnd, _Inout_ LayeredStyle& pStyle) {
  pStyle = LayeredStyle::None;

  auto data = new User32Defines::WindowCompositionAttributeData{};
  if (!SUCCEEDED((*g_fnGetWindowCompositionAttribute)(hWnd, data))) {
    return FALSE;
  }

  if (data == nullptr) {
    return TRUE;
  }

  auto value = static_cast<User32Defines::AccentPolicy*>(data->pvData);

  if (value->AccentState == User32Defines::AccentState::ACCENT_ENABLE_BLURBEHIND) {
    pStyle = LayeredStyle::Aero;
    return TRUE;
  }

  if (value->AccentState == User32Defines::AccentState::ACCENT_ENABLE_ACRYLICBLURBEHIND) {
    pStyle = LayeredStyle::Acrylic;
    return TRUE;
  }

  return TRUE;
}
