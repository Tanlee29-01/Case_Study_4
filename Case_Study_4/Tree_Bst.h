#pragma once

#include "Tree_AVL.h"
#include <iostream>

/**
 * @brief Cây tìm kiếm nhị phân (Binary Search Tree - BST)
 * 
 * Cây nhị phân không tự cân bằng. Mỗi node có tối đa 2 con.
 * Tính chất: node trái < node gốc < node phải
 * 
 * Interface tương thích với AVLTree để có thể thay thế dễ dàng.
 * 
 * @tparam Compare: Hàm so sánh để xác định thứ tự (theo mã môn, tên môn, thời gian)
 */
template <typename Compare>
class BST {
private:
    // Cấu trúc Node của cây BST
    struct BSTNode {
        Class* data;        // Dữ liệu lưu trong node
        BSTNode* left;      // Con trỏ đến node con trái
        BSTNode* right;     // Con trỏ đến node con phải

        explicit BSTNode(Class* pClass)
            : data(pClass), left(nullptr), right(nullptr) {}
    };

    BSTNode* root;      // Con trỏ đến node gốc của cây
    Compare comp;       // Đối tượng dùng để so sánh các phần tử

    /**
     * @brief Chèn một phần tử vào cây BST (hàm đệ quy)
     * Logic giống AVLTree: nhỏ hơn -> trái, lớn hơn -> phải, trùng lặp -> phải
     */
    BSTNode* insert(BSTNode* node, Class* pClass) {
        if (node == nullptr) {
            return new BSTNode(pClass);
        }
        
        // So sánh để quyết định chèn vào bên trái hay phải
        if (comp(pClass, node->data)) {
            // pClass < node->data -> chèn vào cây con trái
            node->left = insert(node->left, pClass);
        }
        else if (comp(node->data, pClass)) {
            // node->data < pClass -> chèn vào cây con phải
            node->right = insert(node->right, pClass);
        }
        else {
            // Trùng lặp khóa -> chèn vào cây con phải (giống AVLTree)
            node->right = insert(node->right, pClass);
        }
        
        return node;
    }

    /**
     * @brief Tìm node có giá trị nhỏ nhất trong cây con
     * Dùng để tìm node thay thế khi xóa node có 2 con
     */
    BSTNode* minValueNode(BSTNode* node) {
        if (node == nullptr) return nullptr;
        
        BSTNode* current = node;
        // Đi về bên trái cho đến khi không còn node nào
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    /**
     * @brief Xóa một node khỏi cây BST (hàm đệ quy)
     * 3 trường hợp: không con, 1 con, 2 con
     * Logic giống AVLTree (không có phần cân bằng)
     */
    BSTNode* deleteNode(BSTNode* node, Class* pClass) {
        if (node == nullptr) return nullptr;

        // Tìm node cần xóa
        if (comp(pClass, node->data)) {
            // pClass < node->data -> tìm ở cây con trái
            node->left = deleteNode(node->left, pClass);
        }
        else if (comp(node->data, pClass)) {
            // pClass > node->data -> tìm ở cây con phải
            node->right = deleteNode(node->right, pClass);
        }
        else {
            // Đã tìm thấy node cần xóa (pClass == node->data)
            
            // Trường hợp 1: Không có con trái (có thể có hoặc không có con phải)
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;  // Chỉ xóa Node, không xóa data (data được quản lý bởi Function)
                return temp;
            }
            
            // Trường hợp 2: Không có con phải (chắc chắn có con trái)
            if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;  // Chỉ xóa Node, không xóa data
                return temp;
            }
            
            // Trường hợp 3: Có cả 2 con -> tìm node nhỏ nhất ở cây con phải để thay thế
            BSTNode* temp = minValueNode(node->right);
            node->data = temp->data;  // Copy dữ liệu
            node->right = deleteNode(node->right, temp->data);  // Xóa node thay thế
        }
        
        return node;
    }

    /**
     * @brief Tìm kiếm một phần tử trong cây BST (hàm đệ quy)
     * So sánh key với node hiện tại, đi trái nếu nhỏ hơn, đi phải nếu lớn hơn
     * Logic giống AVLTree
     */
    template <typename KeyType>
    Class* search(BSTNode* node, const KeyType& key) {
        if (node == nullptr) {
            return nullptr;
        }

        // Dùng compareKey để so sánh (trả về -1, 0, 1)
        int cmpResult = comp.compareKey(key, node->data);
        
        if (cmpResult < 0) {
            // key < node->data -> tìm ở cây con trái
            return search(node->left, key);
        }
        if (cmpResult > 0) {
            // key > node->data -> tìm ở cây con phải
            return search(node->right, key);
        }
        
        // key == node->data -> tìm thấy!
        return node->data;
    }

    /**
     * @brief Duyệt cây theo thứ tự giữa (In-order)
     * Duyệt trái -> xử lý node -> duyệt phải
     * Kết quả: in các phần tử theo thứ tự tăng dần
     * Format giống AVLTree
     */
    void inOrder(BSTNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            node->data->show_infor();
            std::cout << "--------------------" << std::endl;
            inOrder(node->right);
        }
    }

    /**
     * @brief Hủy toàn bộ cây, giải phóng bộ nhớ
     * Duyệt post-order: hủy trái -> hủy phải -> xóa node
     * Lưu ý: Chỉ xóa Node, không xóa data (data được quản lý bởi Function)
     */
    void destroyTree(BSTNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;  // Chỉ xóa Node, không xóa node->data
        }
    }

public:
    // Khởi tạo cây BST rỗng
    BST() : root(nullptr) {}

    // Hủy cây, giải phóng bộ nhớ
    ~BST() {
        destroyTree(root);
    }

    // Chèn một phần tử vào cây
    void insert(Class* pClass) {
        if (pClass == nullptr) return;
        root = insert(root, pClass);
    }

    // Xóa một phần tử khỏi cây
    void remove(Class* pClass) {
        if (pClass == nullptr) return;
        root = deleteNode(root, pClass);
    }

    // Tìm kiếm một phần tử theo key
    template <typename KeyType>
    Class* searchByKey(const KeyType& key) {
        return search(root, key);
    }

    // In toàn bộ cây theo thứ tự tăng dần
    void printInOrder() {
        if (root == nullptr) {
            std::cout << "  (Danh sach rong)" << std::endl;
            return;
        }
        inOrder(root);
    }
};

// Khai báo các template class cụ thể để sử dụng
extern template class BST<CompareByMaMon>;
extern template class BST<CompareByTenMon>;
extern template class BST<CompareByThoiGian>;
