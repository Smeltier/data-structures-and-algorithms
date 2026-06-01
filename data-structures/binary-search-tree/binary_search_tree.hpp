#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class BinarySearchTree {
private:

    struct Node {
        T value;
        Node* left;
        Node* right;

        Node(const T value) : value(value), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;
    std::size_t current_size = 0;

    void clear_node(Node* root) {
        if (!root) return;
        clear_node(root->left);
        clear_node(root->right);
        delete root;
    }

    Node* insert_node(Node* root, const T value) {
        if (!root) {
            return new Node(value);
        }
        if (value < root->value) {
            root->left = insert_node(root->left, value);
        } else {
            root->right = insert_node(root->right, value);
        }
        return root;
    }

    Node* best_node(Node* root) {
        if (!root) {
            return nullptr;
        }

        if (root->left) {
            return best_node(root->left);
        }

        return root;
    }

    Node* remove_node(Node* root, const T value) {
        if (!root) {
            return nullptr;
        }

        if (value < root->value) {
            root->left = remove_node(root->left, value);
        } else if (value > root->value) {
            root->right = remove_node(root->right, value);
        } else {
            Node* tmp = nullptr;

            if (!root->left and !root->right) {
                delete root;
                return nullptr;
            } else if (!root->left) {
                tmp = root->right;
                delete root;
                return tmp;
            } else if (!root->right) {
                tmp = root->left;
                delete root;
                return tmp;
            } else {
                tmp = best_node(root->right);
                root->value = tmp->value;
                root->right = remove_node(root->right, tmp->value);
            }
        }

        return root;
    }

    bool find_node(Node* root, const T value) const {
        if (!root) {
            return false;
        }

        if (value == root->value) {
            return true;
        } else if (value < root->value) {
            return find_node(root->left, value);
        } else {
            return find_node(root->right, value);
        }
    }

    void print_node(Node* root) {
        if (!root) return;
        print_node(root->left);
        std::cout << root->value << " ";
        print_node(root->right);
    }

public:

    BinarySearchTree() {}

    ~BinarySearchTree() {
        clear();
    }

    void insert(const T value) {
        root = insert_node(root, value);
        current_size++;
    }

    void remove(const T value) {
        if (empty() || !search(value)) {
            return;
        }
        root = remove_node(root, value);
        current_size--;
    }

    bool search(const T value) const {
        return find_node(root, value);
    }

    bool empty() const {
        return current_size == 0;
    }

    void print() const {
        if (empty()) return;
        print_node(root);
    }

    void clear() {
        if (empty()) return;
        clear_node(root);
        root = nullptr;
        current_size = 0;
    }

};
