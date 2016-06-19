#pragma once
#include "Includes.h"

class DirectX
{
public:
	DirectX();
	~DirectX();
	void PrintText(char pString[], int x, int y, D3DCOLOR col, ID3DXFont *font);
	void DrawText(const CHAR *text, INT x, INT y, DWORD color);
	int GetTextWidth(const char *szText);
	void FillRGB(int x, int y, int w, int h, D3DCOLOR color);
	void FillBox(int x, int y, int w, int h, D3DCOLOR color, D3DCOLOR color2);
	void DrawTriangle(float x, float y, D3DCOLOR color);
	void DrawMouse(D3DCOLOR color);
	void DrawTab(int x, int y, const char* title, bool &active, int id, D3DCOLOR color);

	LPDIRECT3DDEVICE9 pDev;
	LPD3DXFONT pFont;
};