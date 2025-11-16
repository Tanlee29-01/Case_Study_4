#include "Function.h"
#include <iostream>
#include <string>
#include <limits>     
#include <vector>
#include <chrono>     
#include <sstream>    
#include <iomanip>    

using namespace std;

/**
 * @brief Hàm trợ giúp để xóa bộ đệm cin, tránh bị "trôi lệnh"
 * sau khi dùng cin >> [số]
 */
void clearCinBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ===============================================
// HÀM KHỞI TẠO & HÀM HỦY
// ===============================================

Function::Function() {
    cout << "Dang khoi tao he thong va them du lieu mau..." << endl;
    // ===============================================
    // CHỖ NÀY LÀ DATA NHẬP VÀO ĐỂ TEST XÓA,THÊM,SỬA
    // XÓA ĐƯỢC Á HOẶC GẮN COMMENT CŨNG ĐƯỢC
    // ===============================================
    Class* c1 = new Class("IT001", "Cau truc du lieu", Time(7, 30), "Thay A", 4);
    Class* c2 = new Class("IT002", "Lap trinh huong doi tuong", Time(9, 30), "Co B", 4);
    Class* c3 = new Class("MA001", "Giai tich 1", Time(7, 30), "Thay C", 3);
    Class* c4 = new Class("EN001", "Tieng Anh 1", Time(13, 0), "Co D", 3);
    Class* c5 = new Class("IT003", "Co so lap trinh", Time(9, 30), "Thay A", 4);

    danhSachLop.push_back(c1);
    danhSachLop.push_back(c2);
    danhSachLop.push_back(c3);
    danhSachLop.push_back(c4);
    danhSachLop.push_back(c5);

    for (Class* pClass : danhSachLop) {
        treeTheoMa.insert(pClass);
        treeTheoTen.insert(pClass);
        treeTheoThoiGian.insert(pClass);
    }
    cout << "Da them " << danhSachLop.size() << " lop hoc mau." << endl;
}

Function::~Function() {
    cout << "\nDang don dep bo nho..." << endl;
    for (Class* pClass : danhSachLop) {
        delete pClass;
        pClass = nullptr;
    }
    cout << "Da don dep bo nho. Tam biet!" << endl;
}

// ===============================================
// HÀM TRỢ GIÚP (PRIVATE)
// ===============================================

Time Function::Input_Time() {
    int gio, phut;
    while (true) {
        cout << "  - Nhap Gio bat dau (0-23): ";
        cin >> gio;
        cout << "  - Nhap Phut bat dau (0-59): ";
        cin >> phut;

        if (cin.fail() || gio < 0 || gio > 23 || phut < 0 || phut > 59) {
            cout << "  Loi: Thoi gian khong hop le. Vui long nhap lai." << endl;
            cin.clear();
            clearCinBuffer();
        }
        else {
            clearCinBuffer();
            return Time(gio, phut);
        }
    }
}

Class* Function::Pointer_Search_with_ID(const string& Sub_ID) {
    return treeTheoMa.searchByKey(Sub_ID);
}


// ===============================================
// CÁC CHỨC NĂNG CHÍNH (PUBLIC)
// ===============================================

// 1. Thêm Lớp
void Function::Insert_Class() {
    string maMon, tenMon, giangVien;
    int soTinChi;

    cout << "\n--- 1. Them Lop Hoc Moi ---" << endl;
    cout << "Nhap Ma Mon Hoc (vd: IT004): ";
    getline(cin, maMon);

    if (Pointer_Search_with_ID(maMon) != nullptr) {
        cout << "Loi: Ma mon '" << maMon << "' da ton tai. Khong them." << endl;
        return;
    }

    cout << "Nhap Ten Mon Hoc: ";
    getline(cin, tenMon);
    cout << "Nhap Ten Giang Vien: ";
    getline(cin, giangVien);
    cout << "Nhap So Tin Chi: ";
    cin >> soTinChi;
    clearCinBuffer();

    Time thoiGian = Input_Time();

    Class* newClass = new Class(maMon, tenMon, thoiGian, giangVien, soTinChi);

    danhSachLop.push_back(newClass);

    treeTheoMa.insert(newClass);
    treeTheoTen.insert(newClass);
    treeTheoThoiGian.insert(newClass);

    cout << "\n==> Da them thanh cong lop hoc: " << maMon << endl;
}

// 2. Xóa Lớp
void Function::Delete_Class() {
    string maMon;
    cout << "\n--- 2. Xoa Lop Hoc ---" << endl;
    cout << "Nhap Ma Mon Hoc can xoa: ";
    getline(cin, maMon);

    Class* pClass = Pointer_Search_with_ID(maMon);

    if (pClass == nullptr) {
        cout << "Loi: Khong tim thay ma mon '" << maMon << "'." << endl;
        return;
    }

    cout << "Tim thay lop hoc sau. Ban co chac chan muon xoa?" << endl;
    pClass->show_infor();
    cout << "Nhan 'y' de xac nhan xoa: ";
    char confirm;
    cin >> confirm;
    clearCinBuffer();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Da huy thao tac xoa." << endl;
        return;
    }

    treeTheoMa.remove(pClass);
    treeTheoTen.remove(pClass);
    treeTheoThoiGian.remove(pClass);

    for (auto it = danhSachLop.begin(); it != danhSachLop.end(); ++it) {
        if (*it == pClass) {
            danhSachLop.erase(it);
            break;
        }
    }

    delete pClass;
    pClass = nullptr;

    cout << "\n==> Da xoa thanh cong lop hoc: " << maMon << endl;
}

// 3. Cập nhật Lớp
void Function::Update_Class() {
    string maMon;
    cout << "\n--- 3. Cap Nhat Lop Hoc ---" << endl;
    cout << "Nhap Ma Mon Hoc can cap nhat (Khong the thay doi Ma Mon): ";
    getline(cin, maMon);

    Class* pClass = Pointer_Search_with_ID(maMon);

    if (pClass == nullptr) {
        cout << "Loi: Khong tim thay ma mon '" << maMon << "'." << endl;
        return;
    }

    cout << "Thong tin hien tai cua lop hoc:" << endl;
    pClass->show_infor();
    cout << "--------------------" << endl;
    cout << "Nhap thong tin moi (de trong de giu nguyen):" << endl;

    string newTenMon, newGiangVien;
    string tempSoTinChi;
    Time newThoiGian = pClass->Start_Time;

    bool tenDaThayDoi = false;
    bool thoiGianDaThayDoi = false;

    cout << "Ten Mon Moi (Cu: " << pClass->Sub_name << "): ";
    getline(cin, newTenMon);
    if (!newTenMon.empty()) {
        tenDaThayDoi = true;
    }
    else {
        newTenMon = pClass->Sub_name;
    }

    cout << "Giang Vien Moi (Cu: " << pClass->Teacher_name << "): ";
    getline(cin, newGiangVien);
    if (newGiangVien.empty()) {
        newGiangVien = pClass->Teacher_name;
    }

    cout << "So Tin Chi Moi (Cu: " << pClass->Credits << "): ";
    getline(cin, tempSoTinChi);
    int newSoTinChi;
    if (tempSoTinChi.empty()) {
        newSoTinChi = pClass->Credits;
    }
    else {
        newSoTinChi = stoi(tempSoTinChi);
    }

    cout << "Cap nhat thoi gian? (y/n): ";
    char choice;
    cin >> choice;
    clearCinBuffer();
    if (choice == 'y' || choice == 'Y') {
        newThoiGian = Input_Time();
        if (!(newThoiGian == pClass->Start_Time)) {
            thoiGianDaThayDoi = true;
        }
    }

    if (tenDaThayDoi) {
        treeTheoTen.remove(pClass);
    }
    if (thoiGianDaThayDoi) {
        treeTheoThoiGian.remove(pClass);
    }

    pClass->Sub_name = newTenMon;
    pClass->Teacher_name = newGiangVien;
    pClass->Credits = newSoTinChi;
    pClass->Start_Time = newThoiGian;

    if (tenDaThayDoi) {
        treeTheoTen.insert(pClass);
    }
    if (thoiGianDaThayDoi) {
        treeTheoThoiGian.insert(pClass);
    }

    cout << "\n==> Da cap nhat thanh cong cho lop: " << maMon << endl;
    pClass->show_infor();
}

// 4. Tìm theo ID
void Function::Search_By_ID() {
    string maMon;
    cout << "\n--- 4. Tim Kiem theo Ma Mon Hoc ---" << endl;
    cout << "Nhap Ma Mon Hoc can tim: ";
    getline(cin, maMon);

    Class* pClass = Pointer_Search_with_ID(maMon);
    if (pClass != nullptr) {
        cout << "Tim thay 1 ket qua:" << endl;
        pClass->show_infor();
    }
    else {
        cout << "Khong tim thay lop hoc nao voi ma: " << maMon << endl;
    }
}

// 5. Tìm theo Tên
void Function::Search_By_Name() {
    string tenMon;
    cout << "\n--- 5. Tim Kiem theo Ten Mon Hoc ---" << endl;
    cout << "Nhap Ten Mon Hoc can tim: ";
    getline(cin, tenMon);

    Class* pClass = treeTheoTen.searchByKey(tenMon);
    if (pClass != nullptr) {
        cout << "Tim thay 1 ket qua (co the co nhieu hon):" << endl;
        pClass->show_infor();
    }
    else {
        cout << "Khong tim thay lop hoc nao voi ten: " << tenMon << endl;
    }
}

// 6. In theo Mã Môn
void Function::Show_Sub_ID() {
    cout << "\n=== 6. DANH SACH LOP HOC (SAP XEP THEO MA MON) ===" << endl;
    treeTheoMa.printInOrder();
    cout << "=================================================" << endl;
}

// 7. In theo Tên Môn
void Function::Show_Sub_Name() {
    cout << "\n=== 7. DANH SACH LOP HOC (SAP XEP THEO TEN MON) ===" << endl;
    treeTheoTen.printInOrder();
    cout << "===================================================" << endl;
}

// 8. In theo Thời Gian
void Function::Show_Time() {
    cout << "\n=== 8. DANH SACH LOP HOC (SAP XEP THEO THOI GIAN) ===" << endl;
    treeTheoThoiGian.printInOrder();
    cout << "=====================================================" << endl;
}

// 9. Test Hiệu Năng
void Function::Test_Performance() {

    cout << "\n--- 9. Kiem Tra Hieu Nang (AVL vs BST) ---" << endl;
    cout << "Chuc nang test hieu nang dang duoc phat trien." << endl;
    cout << "Nguoi 3 (Engine) can tao file 'Tree_Bst.h'." << endl;
    cout << "Nguoi 4 (QA) se viet code so sanh o mot file rieng." << endl;
}