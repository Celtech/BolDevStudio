#pragma once
#include "Includes.h"
#include "DirectX.h"
#include "Console.h"

class Menu
{
public:
	Menu(DirectX* dx);
	~Menu();

	void CreateMenu();

private:
	DirectX* directX;
	Console* console;
};


