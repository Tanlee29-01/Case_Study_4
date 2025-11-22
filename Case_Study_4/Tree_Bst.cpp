#include "Tree_Bst.h"

/**
 * @file Tree_Bst.cpp
 * @brief File cài đặt các template class cụ thể cho BST
 * 
 * File này chứa các khai báo template cụ thể (template instantiation)
 * để compiler biết cần tạo code cho những kiểu BST nào.
 * 
 * Có 3 loại BST được sử dụng:
 * 1. BST<CompareByMaMon>: Cây BST sắp xếp theo mã môn học
 * 2. BST<CompareByTenMon>: Cây BST sắp xếp theo tên môn học
 * 3. BST<CompareByThoiGian>: Cây BST sắp xếp theo thời gian
 */

// Tạo code cụ thể cho BST sắp xếp theo mã môn học
template class BST<CompareByMaMon>;

// Tạo code cụ thể cho BST sắp xếp theo tên môn học
template class BST<CompareByTenMon>;

// Tạo code cụ thể cho BST sắp xếp theo thời gian
template class BST<CompareByThoiGian>;
