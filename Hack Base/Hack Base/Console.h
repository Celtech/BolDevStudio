#pragma once
#include "Includes.h"
#include "DirectX.h"

class Console
{
public:
	Console(DirectX* dx);
	void Render(int x, int y, int width, LPDIRECT3DDEVICE9 pDevice);
	void Send(string cmd);
	string command;
	vector<string> prevCommands;
	int caretPos, cmdCount, currCmd;
	int caretTick = 0;
	bool showCaret;
	void GetInput();

	bool active = false;

private:
	DirectX* directX;
	bool shift = false;
	int width = 1;
	int maxWidth = 0;
};