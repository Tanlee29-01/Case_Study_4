#pragma once
#include "DataTypes.h" 
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
struct Node {
    Class* data; 
    Node* left;
    Node* right;
    int height;    

    Node(Class* pClass) : data(pClass), left(nullptr), right(nullptr), height(1) {}
};

struct CompareByMaMon {
    bool operator()(const Class* a, const Class* b) const {
        return a->Sub_id < b->Sub_id;
    }

    int compareKey(const string& key, const Class* data) const {
        if (key < data->Sub_id) return -1;
        if (key > data->Sub_id) return 1;
        return 0;
    }
};

struct CompareByTenMon {
    bool operator()(const Class* a, const Class* b) const {
        return a->Sub_name < b->Sub_name;
    }

    int compareKey(const string& key, const Class* data) const {
        if (key < data->Sub_name) return -1;
        if (key > data->Sub_name) return 1;
        return 0;
    }
};

struct CompareByThoiGian {
    bool operator()(const Class* a, const Class* b) const {
        return a->Start_Time < b->Start_Time;
    }

    int compareKey(const Time& key, const Class* data) const {
        if (key < data->Start_Time) return -1;
        if (key > data->Start_Time) return 1;
        return 0;
    }
};

template <typename Compare>
class AVLTree {
private:
    Node* root;      
    Compare comp;    
    int getHeight(Node* N) {
        if (N == nullptr) return 0;
        return N->height;
    }

    // Tính hệ số cân bằng
    int getBalance(Node* N) {
        if (N == nullptr) return 0;
        return getHeight(N->left) - getHeight(N->right);
    }

    // Hàm xoay phải (Right Rotation)
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    // Hàm xoay trái (Left Rotation)
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }


    Node* insert(Node* node, Class* pClass) {
        // 1. Chèn BST thông thường
        if (node == nullptr) {
            return(new Node(pClass));
        }

        // Dùng `comp` (bộ so sánh) để quyết định đi trái hay phải
        if (comp(pClass, node->data)) { 
            // pClass < node->data
            node->left = insert(node->left, pClass);
        }
        else if (comp(node->data, pClass)) { 
            // node->data < pClass
            node->right = insert(node->right, pClass);
        }
        else {
            // Trùng lặp khóa
            node->right = insert(node->right, pClass);
        }

        // 2. Cập nhật chiều cao
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // 3. Cân bằng cây
        int balance = getBalance(node);

        // Trường hợp LL
        if (balance > 1 && comp(pClass, node->left->data))
            return rightRotate(node);

        // Trường hợp RR
        if (balance < -1 && comp(node->right->data, pClass))
            return leftRotate(node);

        // Trường hợp LR
        if (balance > 1 && comp(node->left->data, pClass)) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Trường hợp RL
        if (balance < -1 && comp(pClass, node->right->data)) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Trả về node (không thay đổi)
        return node;
    }

    // Hàm tìm node có giá trị nhỏ nhất (dùng cho xóa)
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }


    Node* deleteNode(Node* root, Class* pClass) {
        // 1. Xóa BST thông thường
        if (root == nullptr) return root;

        if (comp(pClass, root->data)) { // Key < root->data
            root->left = deleteNode(root->left, pClass);
        }
        else if (comp(root->data, pClass)) { // Key > root->data
            root->right = deleteNode(root->right, pClass);
        }
        else {
            // Đã tìm thấy node cần xóa
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else {
                    *root = *temp;
                }
                delete temp;
            }
            else {
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr) return root;

        // 2. Cập nhật chiều cao
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // 3. Cân bằng lại cây
        int balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    template <typename KeyType>
    Class* search(Node* root, const KeyType& key) {
        if (root == nullptr) {
            return nullptr; 
        }

        int cmpResult = comp.compareKey(key, root->data);

        if (cmpResult < 0) { 
            return search(root->left, key);
        }
        else if (cmpResult > 0) { 
            return search(root->right, key);
        }
        else {
            return root->data; 
        }
    }

    
    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            root->data->show_infor();
            std::cout << "--------------------" << std::endl;
            inOrder(root->right);
        }
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
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