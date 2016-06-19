#pragma once
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <string>
#include <d3d9.h>
#include <Psapi.h>
#include <TlHelp32.h>

class HelperTools
{
public:
	HelperTools();
	~HelperTools();
	void WriteMemory(PVOID pAddress, void *val, int bytes);
	DWORD * FindDevice(VOID);

private:
	inline void SSECopy(void *lpDest, void *lpSource, UINT size);
};

//////////////////////////////////////////////////
//					XOR Strings					//
//////////////////////////////////////////////////
template <int XORSTART, int BUFLEN, int XREFKILLER>

class XorStr
{
private:
	XorStr();
public:
	char s[BUFLEN];

	XorStr(const char * xs);

	~XorStr()
	{
		for (int i = 0; i < BUFLEN; i++) s[i] = 0;
	}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART, BUFLEN, XREFKILLER>::XorStr(const char * xs)
{
	int xvalue = XORSTART;
	int i = 0;

	for (; i < (BUFLEN - 1); i++)
	{
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;//1
		xvalue %= 512;//256
	}

	s[BUFLEN - 1] = 0;
}
