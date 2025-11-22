#include "Function.h"
#include "Tree_Bst.h" // <--- QUAN TRONG: Them file nay de so sanh
#include <iostream>
#include <string>
#include <limits>     
#include <vector>
#include <chrono>     
#include <sstream>    
#include <iomanip>    
#include <random>     // <--- Them thu vien Random

using namespace std;
using namespace std::chrono; // De do thoi gian

/**
 * @brief Hàm trợ giúp để xóa bộ đệm cin
 */
void clearCinBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ===============================================
// HÀM HỖ TRỢ SINH DỮ LIỆU NGẪU NHIÊN (CHO TEST PERFORMANCE)
// ===============================================
string randomStringFunc(size_t length) {
    const string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static mt19937 generator(random_device{}());
    uniform_int_distribution<> distribution(0, characters.size() - 1);
    string random_string;
    for (size_t i = 0; i < length; ++i) {
        random_string += characters[distribution(generator)];
    }
    return random_string;
}

// ===============================================
// HÀM KHỞI TẠO & HÀM HỦY
// ===============================================

Function::Function() {
    // Khởi tạo dữ liệu mẫu cho chương trình chính
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
}

Function::~Function() {
    cout << "\nDang don dep bo nho..." << endl;
    for (Class* pClass : danhSachLop) {
        delete pClass;
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

    // Xoa khoi vector
    for (auto it = danhSachLop.begin(); it != danhSachLop.end(); ++it) {
        if (*it == pClass) {
            danhSachLop.erase(it);
            break;
        }
    }

    delete pClass;
    cout << "\n==> Da xoa thanh cong lop hoc: " << maMon << endl;
}

// 3. Cập nhật Lớp
void Function::Update_Class() {
    string maMon;
    cout << "\n--- 3. Cap Nhat Lop Hoc ---" << endl;
    cout << "Nhap Ma Mon Hoc can cap nhat: ";
    getline(cin, maMon);

    Class* pClass = Pointer_Search_with_ID(maMon);

    if (pClass == nullptr) {
        cout << "Loi: Khong tim thay ma mon '" << maMon << "'." << endl;
        return;
    }

    cout << "Thong tin hien tai:" << endl;
    pClass->show_infor();
    cout << "--------------------" << endl;
    cout << "Nhap thong tin moi (Enter de giu nguyen):" << endl;

    string newTenMon, newGiangVien, tempSoTinChi;
    Time newThoiGian = pClass->Start_Time;
    bool tenChange = false, timeChange = false;

    cout << "Ten Mon Moi (Cu: " << pClass->Sub_name << "): ";
    getline(cin, newTenMon);
    if (!newTenMon.empty()) tenChange = true;
    else newTenMon = pClass->Sub_name;

    cout << "Giang Vien Moi (Cu: " << pClass->Teacher_name << "): ";
    getline(cin, newGiangVien);
    if (newGiangVien.empty()) newGiangVien = pClass->Teacher_name;

    cout << "So Tin Chi Moi (Cu: " << pClass->Credits << "): ";
    getline(cin, tempSoTinChi);
    int newSoTinChi = tempSoTinChi.empty() ? pClass->Credits : stoi(tempSoTinChi);

    cout << "Cap nhat thoi gian? (y/n): ";
    char choice;
    cin >> choice;
    clearCinBuffer();
    if (choice == 'y' || choice == 'Y') {
        newThoiGian = Input_Time();
        if (!(newThoiGian == pClass->Start_Time)) timeChange = true;
    }

    // Xoa khoi cac cay phu thuoc vao key bi thay doi
    if (tenChange) treeTheoTen.remove(pClass);
    if (timeChange) treeTheoThoiGian.remove(pClass);

    // Cap nhat data
    pClass->Sub_name = newTenMon;
    pClass->Teacher_name = newGiangVien;
    pClass->Credits = newSoTinChi;
    pClass->Start_Time = newThoiGian;

    // Them lai vao cay
    if (tenChange) treeTheoTen.insert(pClass);
    if (timeChange) treeTheoThoiGian.insert(pClass);

    cout << "\n==> Da cap nhat thanh cong!" << endl;
}

// 4, 5, 6, 7, 8: Các hàm tìm kiếm và hiển thị (Giữ nguyên logic cũ)
void Function::Search_By_ID() {
    string maMon;
    cout << "\n--- 4. Tim Kiem theo Ma Mon Hoc ---" << endl;
    cout << "Nhap Ma Mon Hoc: ";
    getline(cin, maMon);
    Class* pClass = Pointer_Search_with_ID(maMon);
    if (pClass) pClass->show_infor();
    else cout << "Khong tim thay!" << endl;
}

void Function::Search_By_Name() {
    string tenMon;
    cout << "\n--- 5. Tim Kiem theo Ten Mon Hoc ---" << endl;
    cout << "Nhap Ten Mon Hoc: ";
    getline(cin, tenMon);
    Class* pClass = treeTheoTen.searchByKey(tenMon);
    if (pClass) pClass->show_infor();
    else cout << "Khong tim thay!" << endl;
}

void Function::Show_Sub_ID() {
    cout << "\n=== DANH SACH THEO MA MON ===" << endl;
    treeTheoMa.printInOrder();
}

void Function::Show_Sub_Name() {
    cout << "\n=== DANH SACH THEO TEN MON ===" << endl;
    treeTheoTen.printInOrder();
}

void Function::Show_Time() {
    cout << "\n=== DANH SACH THEO THOI GIAN ===" << endl;
    treeTheoThoiGian.printInOrder();
}

// ===============================================
// 9. TEST HIỆU NĂNG (HOÀN THIỆN)
// ===============================================
void Function::Test_Performance() {
    cout << "\n================================================" << endl;
    cout << "   KIEM TRA HIEU NANG: AVL vs BST" << endl;
    cout << "================================================" << endl;

    int n;
    cout << "Nhap so luong phan tu muon test (VD: 10000): ";
    cin >> n;
    clearCinBuffer();

    if (n <= 0) n = 1000;

    cout << "Dang sinh " << n << " phan tu du lieu mau..." << endl;

    // 1. Tạo dữ liệu mẫu (Chỉ dùng tạm trong hàm này)
    vector<Class*> testData;
    for (int i = 0; i < n; ++i) {
        // Tạo ID ngẫu nhiên nhưng đảm bảo duy nhất bằng index
        string id = "TEST" + to_string(i) + randomStringFunc(3); 
        string name = "Mon Hoc " + randomStringFunc(5);
        testData.push_back(new Class(id, name, Time(8,0), "GV Test", 3));
    }

    // 2. Khai báo 2 cây cục bộ để test
    BST<CompareByMaMon> bstTree;
    AVLTree<CompareByMaMon> avlTree;

    cout << "Du lieu da san sang. Bat dau do..." << endl << endl;

    // --- TEST BST ---
    cout << "--- [BST] ---" << endl;
    
    // Đo Insert BST
    auto start = high_resolution_clock::now();
    for (auto* item : testData) {
        bstTree.insert(item);
    }
    auto stop = high_resolution_clock::now();
    auto durationInsertBST = duration_cast<milliseconds>(stop - start);
    cout << "  -> Thoi gian INSERT " << n << " phan tu: " << durationInsertBST.count() << " ms" << endl;

    // Đo Search BST
    start = high_resolution_clock::now();
    for (auto* item : testData) {
        bstTree.searchByKey(item->Sub_id);
    }
    stop = high_resolution_clock::now();
    auto durationSearchBST = duration_cast<milliseconds>(stop - start);
    cout << "  -> Thoi gian SEARCH " << n << " phan tu: " << durationSearchBST.count() << " ms" << endl;


    // --- TEST AVL ---
    cout << "\n--- [AVL TREE] ---" << endl;

    // Đo Insert AVL
    start = high_resolution_clock::now();
    for (auto* item : testData) {
        avlTree.insert(item);
    }
    stop = high_resolution_clock::now();
    auto durationInsertAVL = duration_cast<milliseconds>(stop - start);
    cout << "  -> Thoi gian INSERT " << n << " phan tu: " << durationInsertAVL.count() << " ms" << endl;

    // Đo Search AVL
    start = high_resolution_clock::now();
    for (auto* item : testData) {
        avlTree.searchByKey(item->Sub_id);
    }
    stop = high_resolution_clock::now();
    auto durationSearchAVL = duration_cast<milliseconds>(stop - start);
    cout << "  -> Thoi gian SEARCH " << n << " phan tu: " << durationSearchAVL.count() << " ms" << endl;

    // --- KẾT LUẬN ---
    cout << "\n------------------------------------------------" << endl;
    cout << "KET QUA SO SANH:" << endl;
    cout << "  - Insert: BST (" << durationInsertBST.count() << "ms) vs AVL (" << durationInsertAVL.count() << "ms)" << endl;
    cout << "  - Search: BST (" << durationSearchBST.count() << "ms) vs AVL (" << durationSearchAVL.count() << "ms)" << endl;
    cout << "------------------------------------------------" << endl;

    // Dọn dẹp bộ nhớ tạm
    cout << "Dang don dep du lieu test..." << endl;
    for (auto* item : testData) {
        delete item;
    }
    cout << "Hoan tat test hieu nang." << endl;
}