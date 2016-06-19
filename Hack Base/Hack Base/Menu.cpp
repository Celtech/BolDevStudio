#include "Menu.h"

Menu::Menu(DirectX* dx)
{
	directX = dx;
	console = new Console(dx);
}

Menu::~Menu()
{
}

void Menu::CreateMenu()
{
	directX->FillBox(5, 5, 400, 300, D3DCOLOR_ARGB(255, 0, 170, 255), D3DCOLOR_ARGB(255, 0, 0, 0));
	directX->FillBox(5, 5, 400, 20, D3DCOLOR_ARGB(255, 255, 255, 255), D3DCOLOR_ARGB(255, 0, 0, 0));
	directX->FillBox(11, 62, 388, 200, D3DCOLOR_ARGB(255, 255, 255, 255), D3DCOLOR_ARGB(255, 0, 0, 0)); //32
	directX->DrawTextA("Some Menu Title", 9, 7, D3DCOLOR_ARGB(255, 0, 0, 0));
	bool test = true;
	bool test2 = false;
	directX->DrawTab(11, 42, "Console", test, 0, 0xFFFFFFFF);
	directX->DrawTab(11, 42, "Aimbot", test2, 1, 0xFFFFFFFF);
	directX->DrawTab(11, 42, "ESP", test2, 2, 0xFFFFFFFF);
	directX->DrawTab(11, 42, "Misc.", test2, 3, 0xFFFFFFFF);
	//console->Render(5,5,500,directX->pDev);
	//directX->DrawMouse(D3DCOLOR_ARGB(255, 255, 255, 255));
}
