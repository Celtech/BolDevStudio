#include "Console.h"

void Console::Send(string cmd)
{

}


Console::Console(DirectX * dx)
{
	directX = dx;
	command = "";
	caretPos = 0;
	cmdCount = 0;
	currCmd = 0;
}

void Console::Render(int x, int y, int width, LPDIRECT3DDEVICE9 pDevice)
{
	directX->FillBox(x, y, width, 20, D3DCOLOR_ARGB(255, 255, 255, 255), D3DCOLOR_ARGB(255, 54, 153, 186));


	caretTick += 1;
	if (caretTick >= 25)
	{
		caretTick = 0;
		showCaret = !showCaret;
	}
	GetInput();


	if (directX->GetTextWidth(command.c_str()) < width) {
		directX->DrawTextA(command.c_str(), x + 2, y + 2, D3DCOLOR_ARGB(255, 0, 0, 0));

		if (showCaret) {
			int stringWidth = directX->GetTextWidth(command.substr(0, caretPos).c_str());
			directX->PrintText("|", x + 2 + stringWidth, y + 2, D3DCOLOR_ARGB(255, 0, 0, 0), directX->pFont);
		}
		maxWidth = caretPos;
	}
}

void Console::GetInput()
{
	if (caretPos < 47) {
		if (GetAsyncKeyState(0x41) & 1) {
			command.insert(caretPos, 1, 'a');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x42) & 1) {
			command.insert(caretPos, 1, 'b');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x43) & 1) {
			command.insert(caretPos, 1, 'c');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x44) & 1) {
			command.insert(caretPos, 1, 'd');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x45) & 1) {
			command.insert(caretPos, 1, 'e');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x46) & 1) {
			command.insert(caretPos, 1, 'f');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x47) & 1) {
			command.insert(caretPos, 1, 'g');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x48) & 1) {
			command.insert(caretPos, 1, 'h');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x49) & 1) {
			command.insert(caretPos, 1, 'i');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x4A) & 1) {
			command.insert(caretPos, 1, 'j');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x4B) & 1) {
			command.insert(caretPos, 1, 'k');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x4C) & 1) {
			command.insert(caretPos, 1, 'l');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x4D) & 1) {
			command.insert(caretPos, 1, 'm');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x4E) & 1) {
			command.insert(caretPos, 1, 'n');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x4F) & 1) {
			command.insert(caretPos, 1, 'o');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x50) & 1) {
			command.insert(caretPos, 1, 'p');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x51) & 1) {
			command.insert(caretPos, 1, 'q');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x52) & 1) {
			command.insert(caretPos, 1, 'r');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x53) & 1) {
			command.insert(caretPos, 1, 's');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x54) & 1) {
			command.insert(caretPos, 1, 't');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x55) & 1) {
			command.insert(caretPos, 1, 'u');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x56) & 1) {
			command.insert(caretPos, 1, 'v');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x57) & 1) {
			command.insert(caretPos, 1, 'w');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x58) & 1) {
			command.insert(caretPos, 1, 'x');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x59) & 1) {
			command.insert(caretPos, 1, 'y');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x5A) & 1) {
			command.insert(caretPos, 1, 'z');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0x20) & 1) {
			command.insert(caretPos, 1, ' ');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0xBE) & 1) {
			command.insert(caretPos, 1, '.');
			caretPos += 1;
		}
		else if (GetAsyncKeyState(0xBB) & 1) {
			command.insert(caretPos, 1, '=');
			caretPos += 1;
		}
		
	}

	if (GetAsyncKeyState(0x08) & 1) {
		if (caretPos > 0)
		{
			command.erase(caretPos - 1, 1);
			caretPos -= 1;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT) & 1) {
		if (caretPos > 0) caretPos -= 1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 1) {
		if (caretPos < (int)command.length()) caretPos += 1;
	}
	else if (GetAsyncKeyState(VK_RETURN) & 1) {
		Send(command);
	}
}
