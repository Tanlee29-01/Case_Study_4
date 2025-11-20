#pragma once
#include "Function.h"

class Menu
{

private:
	Function& BoXL;

	void Hienthitieude();
	void Hienthilogo();
	int HienMenu();

public:
	Menu(Function& function);
	~Menu();

	void ChayMenu();
};