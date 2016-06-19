#pragma once
#include "Includes.h"
#include "Menu.h"

typedef HRESULT(__stdcall* oPresent) (LPDIRECT3DDEVICE9 pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);

oPresent pPresent;

Debugging* dbg = new Debugging();
HelperTools* tools = new HelperTools();
DirectX* directX = new DirectX();
Menu* menu = new Menu(directX);