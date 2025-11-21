#include <iostream>
#include "Menu.h"
#include <limits> //hàm hỗ trợ xử lý lỗi nhâp liệu

using namespace std;

Menu::Menu(Function& function) : BoXL(function)
{
    //Gán biến function truyền vào cho biến thành viên BoXL
}

Menu::~Menu()
{
    //kh cần xóa BoXL vì Menu chỉ mượn dùng, kh sở hữu nó
}

//hàm hiển thị tiêu đề
void Menu::Hienthitieude() {
    cout << "=========================================================" << endl;
}

//hàm hiển thị logo
void Menu::Hienthilogo() {
    Hienthitieude();
    cout << "       HE THONG QUAN LY LICH HOC VA THOI KHOA BIEU" << endl;
    cout << "       (Nhom 4: Menu C++)" << endl;
    Hienthitieude();
}

//hàm hiển thị menu và nhận lựa chọn từ người dùng
int Menu::HienMenu() {
    int luaChon;
    cout << "Nhap lua chon cua ban:" << endl;
    cin >> luaChon;

    //xử lý lỗi nhập liệu
    if (cin.fail()) {
        cin.clear(); //xóa cờ lỗi
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //xóa bộ đệm nhập
        return -1; //trả về giá trị lỗi
    }

    //xóa bộ đệm tránh trôi getline sau này
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return luaChon;
}

//hàm chạy menu chính
void Menu::ChayMenu() {
    int choice = -1;

    //vòng lâp chính của menu
    while (choice != 0) {
        cout << endl;
        Hienthilogo();

        cout << "1. Them lop hoc moi" << endl;
        cout << "2. Xoa lop hoc" << endl;
        cout << "3. Cap nhat thong tin lop hoc" << endl;
        cout << "4. Tim kiem theo Ma Mon Hoc" << endl;
        cout << "5. Tiem kiem theo Ten Mon Hoc" << endl;
        cout << "6. Hien thi danh sach (theo Ma Mon Hoc)" << endl;
        cout << "7. Hien thi danh sach (theo Ten Mon Hoc)" << endl;
        cout << "8. Hien thi danh sach (theo Thoi Gian)" << endl;
        cout << "9. Kiem tra hieu nang (Demo)" << endl;
        cout << "0. Thoat chuong trinh" << endl;

        Hienthitieude();

        choice = HienMenu();

        switch (choice) {
        case 1:
            BoXL.Insert_Class();
            break;
        case 2:
            BoXL.Delete_Class();
            break;
        case 3:
            BoXL.Update_Class();
            break;
        case 4:
            BoXL.Search_By_ID();
            break;
        case 5:
            BoXL.Search_By_Name();
            break;
        case 6:
            BoXL.Show_Sub_ID();
            break;
        case 7:
            BoXL.Show_Sub_Name();
            break;
        case 8:
            BoXL.Show_Time();
            break;
        case 9:
            BoXL.Test_Performance();
            break;
        case 0:
            cout << "\n  Cam on ban da su dung chuong trinh. Tam biet!\n";
            break;
        default:
            cout << "\n  Lua chon khong hop le. Vui long nhap so tu 0 den 9.\n";
            break;
        }

        //Dừng màn hình để người dùng kịp xem kết quả trước khi in menu
        if (choice != 0) {
            cout << "\n (Nhan Enter de quay lai Menu chinh)";
            cin.get();
        }
    }
}