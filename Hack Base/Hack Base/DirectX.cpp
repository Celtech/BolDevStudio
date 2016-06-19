#include "DirectX.h"



DirectX::DirectX()
{
}


DirectX::~DirectX()
{
}

void DirectX::PrintText(char pString[], int x, int y, D3DCOLOR col, ID3DXFont *font)
{
	RECT FontRect = { x, y, x + 500, y + 30 };
	font->DrawText(NULL, pString, -1, &FontRect, DT_LEFT | DT_WORDBREAK, col);
}

void DirectX::DrawText(const CHAR *text, INT x, INT y, DWORD color) {
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawText(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, color);
}

int DirectX::GetTextWidth(const char *szText)
{
	RECT rcRect = { 0,0,0,0 };
	if (pFont)
	{
		// calculate required rect
		pFont->DrawText(NULL, szText, strlen(szText), &rcRect, DT_CALCRECT,
			D3DCOLOR_XRGB(0, 0, 0));
	}

	// return width
	return rcRect.right - rcRect.left;
}

void DirectX::FillRGB(int x, int y, int w, int h, D3DCOLOR color)
{
	if (w < 0)w = 1;
	if (h < 0)h = 1;
	if (x < 0)x = 1;
	if (y < 0)y = 1;

	D3DRECT rec = { x, y, x + w, y + h };
	pDev->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void DirectX::FillBox(int x, int y, int w, int h, D3DCOLOR color, D3DCOLOR color2)
{
	FillRGB(x - 1, y - 1, w + 2, h + 2, color2);
	FillRGB(x, y, w, h, color);
}

void DirectX::DrawTriangle(float x, float y, D3DCOLOR color)
{
	#define D3DFVF_MYVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
	VOID* pVertices;

	struct MYVERTEX
	{
		FLOAT x, y, z, rhw; 
		DWORD color;
	};

	MYVERTEX Vertices2[] =
	{
		{ x - 1, y - 1, 0.5f, 1.0f, D3DCOLOR_ARGB(255,0,0,0), }, 
		{ x + 16, y + 04, 0.5f, 1.0f, D3DCOLOR_ARGB(255,0,0,0), }, 
		{ x + 07, y + 13, 0.5f, 1.0f, D3DCOLOR_ARGB(255,0,0,0), },
	};

	pDev->CreateVertexBuffer(3 * sizeof(MYVERTEX), 0, D3DFVF_MYVERTEX, D3DPOOL_DEFAULT, &g_pVertexBuffer, NULL);
	g_pVertexBuffer->Lock(0, sizeof(Vertices2), &pVertices, 0);
	memcpy(pVertices, Vertices2, sizeof(Vertices2));
	g_pVertexBuffer->Unlock();

	pDev->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(MYVERTEX));
	pDev->SetFVF(D3DFVF_MYVERTEX);
	pDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);


	MYVERTEX Vertices[] =
	{
		{ x, y, 0.5f, 1.0f, color, },
		{ x + 15, y + 04, 0.5f, 1.0f, color, },
		{ x + 07, y + 12, 0.5f, 1.0f, color, },
	};

	pDev->CreateVertexBuffer(3 * sizeof(MYVERTEX), 0, D3DFVF_MYVERTEX, D3DPOOL_DEFAULT, &g_pVertexBuffer, NULL);
	g_pVertexBuffer->Lock(0, sizeof(Vertices), &pVertices, 0);
	memcpy(pVertices, Vertices, sizeof(Vertices));
	g_pVertexBuffer->Unlock();

	pDev->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(MYVERTEX));
	pDev->SetFVF(D3DFVF_MYVERTEX);
	pDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

void DirectX::DrawMouse(D3DCOLOR color)
{
	POINT cur;
	GetCursorPos(&cur);
	DrawTriangle(cur.x, cur.y, color);
}

void DirectX::DrawTab(int x, int y, const char * title, bool &active, int id, D3DCOLOR color)
{
	if (active) {
		FillRGB(x - 1 + (id * 71), y - 1, 72, 20, 0xFF000000);
		FillRGB(x + (id * 71), y, 70, 20, 0xFFFFFFFF);
	}
	else {
		FillRGB(x + (id * 71) - 1, y - 1, 72, 21, 0xFF000000);
		FillRGB(x + (id * 71), y, 70, 19, 0xFFFFFFFF);
	}

	
	DrawText(title, x + 3 + (id * 71), y + 3, 0xFF000000);
}
