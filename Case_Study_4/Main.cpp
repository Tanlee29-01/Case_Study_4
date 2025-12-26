#include <iostream>
#include "Function.h"
#include "Menu.h"

int main() {
    Function app;
    Menu menu(app);
    menu.ChayMenu();
    return 0;
}
