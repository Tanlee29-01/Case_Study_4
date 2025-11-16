#pragma once

// 1. BAO GỒM file DataTypes của bạn
#include "DataTypes.h" 

// 2. BAO GỒM các thư viện cần thiết
#include <algorithm> // Dùng cho std::max
#include <iostream>  // Dùng để in ra (trong hàm printInOrder)

/**
 * @brief Cấu trúc Node cho cây AVL.
 * [MENTOR'S NOTE]: Nó sẽ lưu một con trỏ 'Class*' trỏ đến
 * đối tượng Class mà bạn tạo.
 */
struct Node {
    Class* data; // <-- Dùng 'Class*' theo định nghĩa của bạn
    Node* left;
    Node* right;
    int height;    // Chiều cao của node này (cần cho cân bằng)

    // Hàm khởi tạo Node
    Node(Class* pClass) : data(pClass), left(nullptr), right(nullptr), height(1) {}
};

// ===================================================================
// CÁC BỘ SO SÁNH (FUNCTORS) - ĐÃ ĐIỀU CHỈNH
// [MENTOR'S NOTE]: Đây là phần "ma thuật". Nó cho phép 1 code AVLTree
// có thể sắp xếp theo 3 cách khác nhau.
// ===================================================================

/**
 * @brief Bộ so sánh theo MÃ MÔN HỌC (Sub_id)
 */
struct CompareByMaMon {
    // 1. So sánh 2 đối tượng Class* (dùng khi chèn, xóa, cân bằng)
    bool operator()(const Class* a, const Class* b) const {
        // Dùng 'Sub_id' từ class Class của bạn
        return a->Sub_id < b->Sub_id;
    }

    // 2. So sánh 1 key (string) với 1 đối tượng Class* (dùng khi tìm kiếm)
    // Trả về: -1 (key < data), 0 (key == data), 1 (key > data)
    int compareKey(const std::string& key, const Class* data) const {
        if (key < data->Sub_id) return -1;
        if (key > data->Sub_id) return 1;
        return 0; // Bằng nhau
    }
};

/**
 * @brief Bộ so sánh theo TÊN MÔN HỌC (Sub_name)
 */
struct CompareByTenMon {
    // 1. So sánh 2 đối tượng Class*
    bool operator()(const Class* a, const Class* b) const {
        // Dùng 'Sub_name' từ class Class của bạn
        return a->Sub_name < b->Sub_name;
    }

    // 2. So sánh 1 key (string) với 1 đối tượng Class*
    int compareKey(const std::string& key, const Class* data) const {
        if (key < data->Sub_name) return -1;
        if (key > data->Sub_name) return 1;
        return 0;
    }
};

/**
 * @brief Bộ so sánh theo THỜI GIAN BẮT ĐẦU (Start_Time)
 */
struct CompareByThoiGian {
    // 1. So sánh 2 đối tượng Class*
    bool operator()(const Class* a, const Class* b) const {
        // Dùng 'Start_Time' từ class Class của bạn
        // Nó sẽ tự động gọi hàm 'Time::operator<' mà bạn đã viết
        return a->Start_Time < b->Start_Time;
    }

    // 2. So sánh 1 key (Time) với 1 đối tượng Class*
    int compareKey(const Time& key, const Class* data) const {
        // Dùng 'Start_Time' và các toán tử <, > (hoặc ==) của class Time
        if (key < data->Start_Time) return -1;
        if (key > data->Start_Time) return 1; // Có thể không cần cũng đc
        return 0;
    }
};

// ===================================================================
// KHAI BÁO VÀ CÀI ĐẶT LỚP CÂY AVL (TEMPLATE)
// ===================================================================
template <typename Compare>
class AVLTree {
private:
    Node* root;      // Node gốc của cây
    Compare comp;    // Biến comp để gọi các hàm so sánh (ví dụ: comp(a, b))

    // --- CÁC HÀM TRỢ GIÚP (PRIVATE) ---

    // Lấy chiều cao (an toàn khi gọi với nullptr)
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
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    // Hàm xoay trái (Left Rotation)
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    /**
     * @brief Hàm chèn (Insert) đệ quy.
     * [MENTOR'S NOTE]: Tham số là 'Class*' theo class của bạn.
     */
    Node* insert(Node* node, Class* pClass) {
        // 1. Chèn BST thông thường
        if (node == nullptr) {
            return(new Node(pClass));
        }

        // Dùng `comp` (bộ so sánh) để quyết định đi trái hay phải
        if (comp(pClass, node->data)) { // pClass < node->data
            node->left = insert(node->left, pClass);
        }
        else if (comp(node->data, pClass)) { // node->data < pClass
            node->right = insert(node->right, pClass);
        }
        else {
            // Trùng lặp khóa
            node->right = insert(node->right, pClass);
        }

        // 2. Cập nhật chiều cao
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

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

    /**
     * @brief Hàm xóa (Delete) đệ quy.
     * [MENTOR'S NOTE]: Tham số là 'Class*' theo class của bạn.
     */
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
                // [MENTOR'S NOTE]: Chỉ xóa 'Node', KHÔNG xóa 'data' (pClass)
                // vì 'data' sẽ được quản lý bởi lớp Function
                delete temp;
            }
            else {
                // Node có 2 con
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr) return root;

        // 2. Cập nhật chiều cao
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

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

    /**
     * @brief Hàm tìm kiếm (Search) đệ quy
     * Dùng hàm 'compareKey' của bộ so sánh.
     */
    template <typename KeyType>
    Class* search(Node* root, const KeyType& key) {
        if (root == nullptr) {
            return nullptr; // Không tìm thấy
        }

        // Dùng `comp.compareKey` để so sánh (trả về -1, 0, 1)
        int cmpResult = comp.compareKey(key, root->data);

        if (cmpResult < 0) { // key < root->data
            return search(root->left, key);
        }
        else if (cmpResult > 0) { // key > root->data
            return search(root->right, key);
        }
        else {
            return root->data; // Đã tìm thấy! Trả về con trỏ Class*
        }
    }

    /**
     * @brief Duyệt cây theo thứ tự (In-order)
     * Sẽ in ra danh sách đã được sắp xếp.
     */
    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            // [MENTOR'S NOTE]: Gọi hàm 'show_infor' của bạn
            root->data->show_infor();
            std::cout << "--------------------" << std::endl;
            inOrder(root->right);
        }
    }

    // Hàm dọn dẹp bộ nhớ (dùng cho hàm hủy)
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            // [MENTOR'S NOTE]: Chỉ xóa 'Node', không xóa 'node->data'
            delete node;
        }
    }

public:
    // --- CÁC HÀM CÔNG KHAI (PUBLIC API) ---

    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        destroyTree(root);
    }

    // Hàm chèn (wrapper)
    void insert(Class* pClass) {
        if (pClass == nullptr) return;
        root = insert(root, pClass);
    }

    // Hàm xóa (wrapper)
    void remove(Class* pClass) {
        if (pClass == nullptr) return;
        root = deleteNode(root, pClass);
    }

    // Hàm tìm kiếm (wrapper)
    template <typename KeyType>
    Class* searchByKey(const KeyType& key) {
        return search(root, key);
    }

    // Hàm in ra danh sách đã sắp xếp
    void printInOrder() {
        if (root == nullptr) {
            std::cout << "  (Danh sach rong)" << std::endl;
            return;
        }
        inOrder(root);
    }
};