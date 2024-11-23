#pragma once
#include <Windows.h>

#include "dwmapi.interface.h"

#ifndef __USER32_INTERFACE_H__
#define __USER32_INTERFACE_H__

namespace User32Defines {

typedef enum __enumAccentState {
  ACCENT_DISABLED                   = 0,
  ACCENT_ENABLE_GRADIENT            = 1,
  ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
  ACCENT_ENABLE_BLURBEHIND          = 3,
  ACCENT_ENABLE_ACRYLICBLURBEHIND   = 4, // RS4 1803.17063
  ACCENT_ENABLE_HOSTBACKDROP        = 5, // RS5 1809
  ACCENT_INVALID_STATE              = 6
} AccentState;

typedef enum __enumSystemBackdropType { Auto, None, Mica, Acrylic, Tabbed } SystemBackdropType;

typedef enum __enumWindowCompositionAttribute {
  WCA_UNDEFINED                     = 0,
  WCA_NCRENDERING_ENABLED           = 1,
  WCA_NCRENDERING_POLICY            = 2,
  WCA_TRANSITIONS_FORCEDISABLED     = 3,
  WCA_ALLOW_NCPAINT                 = 4,
  WCA_CAPTION_BUTTON_BOUNDS         = 5,
  WCA_NONCLIENT_RTL_LAYOUT          = 6,
  WCA_FORCE_ICONIC_REPRESENTATION   = 7,
  WCA_EXTENDED_FRAME_BOUNDS         = 8,
  WCA_HAS_ICONIC_BITMAP             = 9,
  WCA_THEME_ATTRIBUTES              = 10,
  WCA_NCRENDERING_EXILED            = 11,
  WCA_NCADORNMENTINFO               = 12,
  WCA_EXCLUDED_FROM_LIVEPREVIEW     = 13,
  WCA_VIDEO_OVERLAY_ACTIVE          = 14,
  WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
  WCA_DISALLOW_PEEK                 = 16,
  WCA_CLOAK                         = 17,
  WCA_CLOAKED                       = 18,
  WCA_ACCENT_POLICY                 = 19,
  WCA_FREEZE_REPRESENTATION         = 20,
  WCA_EVER_UNCLOAKED                = 21,
  WCA_VISUAL_OWNER                  = 22,
  WCA_HOLOGRAPHIC                   = 23,
  WCA_EXCLUDED_FROM_DDA             = 24,
  WCA_PASSIVEUPDATEMODE             = 25,
  WCA_LAST                          = 26
} WindowCompositionAttribute;

typedef struct __structWindowCompositionAttributeData {
  WindowCompositionAttribute Attrib;
  PVOID                      pvData;
  SIZE_T                     cbData;
} WindowCompositionAttributeData;

typedef struct __structAccentPolicy {
  AccentState AccentState;
  DWORD       AccentFlags;
  DWORD       GradientColor;
  DWORD       AnimationId;
} AccentPolicy;

} // namespace User32Defines

using fnSetWindowCompositionAttributeType = BOOL(WINAPI*)(_In_ HWND, _In_ User32Defines::WindowCompositionAttributeData*);
using fnGetWindowCompositionAttributeType = BOOL(WINAPI*)(_In_ HWND, _Inout_ User32Defines::WindowCompositionAttributeData*);

#endif // !__USER32_INTERFACE_H__
