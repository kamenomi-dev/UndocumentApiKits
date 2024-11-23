#pragma once
#include "pch.h"

#include "user32.interface.h"

#ifndef __WINDOW_STYLE_H__
#define __WINDOW_STYLE_H__

extern BOOL __stdcall KwsInitialize();
extern BOOL __stdcall KwsUninitialize();

API_EXPORT typedef enum __enumLayeredStyle { None, Aero, Acrylic, Mica } LayeredStyle;

API_EXPORT BOOL KwsSetWindowLayeredStyle(_In_ HWND, _In_ LayeredStyle);
API_EXPORT BOOL KwsGetWindowLayeredStyle(_In_ HWND, _Inout_ LayeredStyle&);

#endif // __WINDOW_STYLE_H__