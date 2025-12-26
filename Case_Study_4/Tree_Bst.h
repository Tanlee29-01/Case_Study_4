#pragma once

#include "Tree_AVL.h"
#include <iostream>

template <typename Compare>
class BST {
private:
    struct BSTNode {
        Class* data;       
        BSTNode* left;      
        BSTNode* right;     

        explicit BSTNode(Class* pClass)
            : data(pClass), left(nullptr), right(nullptr) {}
    };

    BSTNode* root;     
    Compare comp;       
    BSTNode* insert(BSTNode* node, Class* pClass) {
        if (node == nullptr) {
            return new BSTNode(pClass);
        }
        
        if (comp(pClass, node->data)) {
            node->left = insert(node->left, pClass);
        }
        else if (comp(node->data, pClass)) {
            node->right = insert(node->right, pClass);
        }
        else {
            node->right = insert(node->right, pClass);
        }
        
        return node;
    }

    BSTNode* minValueNode(BSTNode* node) {
        if (node == nullptr) return nullptr;
        
        BSTNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

     
    BSTNode* deleteNode(BSTNode* node, Class* pClass) 
    {
        if (node == nullptr) return nullptr;

        if (comp(pClass, node->data)) {
            node->left = deleteNode(node->left, pClass);
        }
        else if (comp(node->data, pClass)) {
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
            node->data = temp->data;  
            node->right = deleteNode(node->right, temp->data);  
        }
        
        return node;
    }

    template <typename KeyType>
    Class* search(BSTNode* node, const KeyType& key) {
        if (node == nullptr) {
            return nullptr;
        }

        int cmpResult = comp.compareKey(key, node->data);
        
        if (cmpResult < 0) {
            return search(node->left, key);
        }
        if (cmpResult > 0) {
            return search(node->right, key);
        }
        
        return node->data;
    }

    void inOrder(BSTNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            node->data->show_infor();
            std::cout << "--------------------" << std::endl;
            inOrder(node->right);
        }
    }

    void destroyTree(BSTNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;  // Chỉ xóa Node, không xóa node->data
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() {
        destroyTree(root);
    }

    void insert(Class* pClass) {
        if (pClass == nullptr) return;
        root = insert(root, pClass);
    }

    void remove(Class* pClass) {
        if (pClass == nullptr) return;
        root = deleteNode(root, pClass);
    }

    template <typename KeyType>
    Class* searchByKey(const KeyType& key) {
        return search(root, key);
    }

    void printInOrder() {
        if (root == nullptr) {
            std::cout << "  (Danh sach rong)" << std::endl;
            return;
        }
        inOrder(root);
    }
};

extern template class BST<CompareByMaMon>;
extern template class BST<CompareByTenMon>;
extern template class BST<CompareByThoiGian>;
