#include "Hook.h"

HRESULT WINAPI PresentHook(LPDIRECT3DDEVICE9 pDevice, CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion)
{
	__asm
	{
		pushad
	}
	
	if (directX->pDev != pDevice) {
		dbg->Message("Creating pDevice");
		directX->pDev = pDevice;
		dbg->Message("Creating Font");
		D3DXCreateFontA(pDevice, 14, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &directX->pFont);
	}

	//rectX->PrintText("test", 4, 4, D3DCOLOR_ARGB(255, 255, 0, 0), directX->pFont);
	menu->CreateMenu();

	__asm
	{
		popad
	}

	return pPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

static DWORD HotPatchDetour(DWORD dwFunction, DWORD dwAddress) { 
	BYTE JMP_JMP_SHORT[7] = { 0xE9, 0x00, 0x00, 0x00, 0x00, 0xEB, 0xF9 };
	DWORD dwNewAddress = (dwAddress - 5); 
	*(DWORD*)(&JMP_JMP_SHORT[1]) = (dwFunction - dwNewAddress) - 5; 
	tools->WriteMemory((void*)dwNewAddress, (PBYTE)JMP_JMP_SHORT, 7); 
	return (dwNewAddress + 7); 
}

void Hook(void)
{
	dbg->Message("Entering Hook");

	DWORD * VtablePtr = tools->FindDevice();
	dbg->Message("VtablePtr = 0x%x", VtablePtr);	

	DWORD * VTable;
	*(DWORD *)&VTable = *(DWORD *)VtablePtr;
	dbg->Message("VTable = 0x%x", VTable);

	pPresent = (oPresent)HotPatchDetour((DWORD)PresentHook, (DWORD)VTable[17]);
}

DWORD __stdcall Initialization(LPVOID)
{
	dbg->Message("Entering Initialization");
	Hook();
	return 0;
}

bool _stdcall DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
		case DLL_PROCESS_ATTACH:
			char fileNameBuffer[4000];
			GetModuleBaseName(GetCurrentProcess(), NULL, fileNameBuffer, MAX_PATH);
			dbg->Message("Dll attached to %s(0x%x)", fileNameBuffer, GetModuleHandleA(fileNameBuffer));
			CreateThread(0, 0, &Initialization, 0, 0, 0);
			break;

		case DLL_PROCESS_DETACH:

			break;
	}

	return true;
}