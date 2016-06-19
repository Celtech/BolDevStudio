#include "HelperTools.h"



HelperTools::HelperTools()
{
}


HelperTools::~HelperTools()
{
}

inline void HelperTools::SSECopy(void *lpDest, void *lpSource, UINT size)
{
	typedef uint32_t u32;
	typedef u32 ptr;
	UINT alignedSize = size & 0xFFFFFFF0;

	if (ptr(lpDest) & 0xF || ptr(lpSource) & 0xF) //if unaligned revert to normal copy
	{
		memcpy(lpDest, lpSource, size);
		return;
	}

	register __m128i *mDest = (__m128i*)lpDest;
	register __m128i *mSrc = (__m128i*)lpSource;

	{
		register UINT numCopies = alignedSize >> 4;
		while (numCopies--)
		{
			_mm_store_si128(mDest, *mSrc);
			mDest++;
			mSrc++;
		}
	}

	{
		UINT sizeTemp = size - alignedSize;
		if (sizeTemp)
			memcpy(mDest, mSrc, sizeTemp);
	}
}

void HelperTools::WriteMemory(PVOID pAddress, void *val, int bytes)
{
	DWORD d, ds;
	VirtualProtect((void*)pAddress, bytes, PAGE_EXECUTE_READWRITE, &d);

	if (memcmp(val, (void*)pAddress, bytes))
		SSECopy((void*)pAddress, val, bytes);

	VirtualProtect((void*)pAddress, bytes, d, &ds);
}

DWORD * HelperTools::FindDevice(VOID)
{
	DWORD Base = (DWORD)LoadLibraryW(L"d3d9.dll");

	for (DWORD i = 0; i < 0x128000; i++)
	{
		if ((*(BYTE *)(Base + i + 0x00)) == 0xC7
			&& (*(BYTE *)(Base + i + 0x01)) == 0x06
			&& (*(BYTE *)(Base + i + 0x06)) == 0x89
			&& (*(BYTE *)(Base + i + 0x07)) == 0x86
			&& (*(BYTE *)(Base + i + 0x0C)) == 0x89
			&& (*(BYTE *)(Base + i + 0x0D)) == 0x86)
			return (DWORD *)(Base + i + 2);
	}
	return NULL;
}