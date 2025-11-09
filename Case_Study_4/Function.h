#pragma once
#include<vector>
#include<string>
#include "DataTypes.h"
#include "Tree_AVL.h"
class Function
{
public:
	//Thêm
	//Xóa
	//Cập nhật
	//Tìm kiếm
	//Sắp xếp
	Function();
	//1. Thêm lớp
	void Insert_Class();
	//2. Xóa Lớp 
	void Delete_Class();
	//3. Cập nhật Lớp học
	void Update_Class();
	//4. Tìm theo ID
	void Search_By_ID();
	//5. Tìm theo Name
	void Search_By_Name();
	//6. In mã môn
	void Show_Sub_ID();
	//7. In tên môn
	void Show_Sub_Name();
	//8. In thời gian
	void Show_Time();
	//9. Test Hiệu năng
	void Test_Performance();
	~Function();

private:
	/*
	================
	=  ID,Tên,Time =
	================ 
	*/ 
	vector<Class*> List_ID;
	vector<string> List_Name;
	vector<int> List_Time;
	AVLTree<CompareByMaMon> tree_id;
	AVLTree<CompareByTenMon> tree_name;
	AVLTree<CompareByThoiGian> tree_time;

	Time Input_Time();

	Class* Pointer_Search_with_ID(const string& Sub_ID);
};

