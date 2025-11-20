#pragma once
#include "Fucntion.h"

class Menu
{

private:
	Fucntion& BoXL;

	void Hienthitieude();
	void Hienthilogo();
	int Menu();

public:
	Menu(Fucntion& fucntion);
	~Menu();

	void ChayMenu();
};
