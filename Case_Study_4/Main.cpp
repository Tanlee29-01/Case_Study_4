#include <iostream>
#include "Function.h"
#include "Menu.h"

int main() {
    //khởi tạo dữ liệu
    Function app;

    //khởi tạo menu và đưa dữ liệu vào
    Menu menu(app);

    //gọi hàm
    menu.ChayMenu();
    return 0;
}
