#pragma once

#include "Tree_AVL.h" 
#include <vector>
#include <string>
using namespace std;

class Function {
public:
    Function();
    ~Function();

    void Insert_Class();
    void Delete_Class();
    void Update_Class();
    void Search_By_ID();
    void Search_By_Name();
    void Show_Sub_ID();
    void Show_Sub_Name();
    void Show_Time();
    void Test_Performance();

private:
    vector<Class*> danhSachLop;

    AVLTree<CompareByMaMon> treeTheoMa;
    AVLTree<CompareByTenMon> treeTheoTen;
    AVLTree<CompareByThoiGian> treeTheoThoiGian;

    Time Input_Time();

    Class* Pointer_Search_with_ID(const std::string& Sub_ID);
};