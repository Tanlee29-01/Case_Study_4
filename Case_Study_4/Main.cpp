// Main.cpp (Dùng để test Menu)
#include "Function.h"
#include "Menu.h"

int main() {
    Function app;    // 1. Tạo app
    Menu menu(app);  // 2. Gắn app vào menu
    menu.ChayChuongTrinh(); // 3. Chạy
    return 0;
}