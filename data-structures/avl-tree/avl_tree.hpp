#pragma once

#include <algorithm>
#include <iostream>

class AVLTree {
public:
    AVLTree() {}

    ~AVLTree() {
        delete_node(root);
    }

    bool search(int value) const {
        return find_node(root, value);
    }

    void print() const {
        print_tree(root, 0);
    }

    void insert(int value) {
        root = insert_node(root, value);
    }

    void remove(int value) {
        root = remove_node(root, value);
    }

private:

    struct Node {
        int data;
        Node* left;
        Node* right;
        int height;

        Node(int data) : data(data) {
            left = nullptr;
            right = nullptr;
            height = 0;
        }
    };

    Node* root = nullptr;

    int height(Node* node) {
        return (node ? node->height : -1);
    }

    int balance_factor(Node* node) {
        return (node ? height(node->left) - height(node->right) : 0);
    }

    Node* min_node(Node* node) {
        if (!node->left) {
            return node;
        }
        return min_node(node->left);
    }

    Node* right_rotate(Node* node) {
        Node* old_left = node->left;
        Node* transferred = old_left->right;

        old_left->right = node;
        node->left = transferred;

        node->height = 1 + std::max(height(node->left), height(node->right));
        old_left->height = 1 + std::max(height(old_left->left), height(old_left->right));

        return old_left;
    }

    Node* left_rotate(Node* node) {
        Node* old_right = node->right;
        Node* transferred = old_right->left;

        old_right->left = node;
        node->right = transferred;

        node->height = 1 + std::max(height(node->left), height(node->right));
        old_right->height = 1 + std::max(height(old_right->left), height(old_right->right));

        return old_right;
    }

    bool find_node(Node* node, int value) const {
        if (!node) return false;

        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return find_node(node->left, value);
        } else {
            return find_node(node->right, value);
        }
    }

    Node* insert_node(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insert_node(node->left, value);
        } else if (value > node->data) {
            node->right = insert_node(node->right, value);
        } else {
            return node;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = balance_factor(node);

        if (balance > 1 and value < node->left->data) {
            return right_rotate(node);
        }

        if (balance < -1 and value > node->right->data) {
            return left_rotate(node);
        }

        if (balance > 1 and value > node->left->data) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }

        if (balance < -1 and value < node->right->data) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        return node;
    }

    Node* remove_node(Node* node, int value) {
        if (!node) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = remove_node(node->left, value);
        } else if (value > node->data) {
            node->right = remove_node(node->right, value);
        } else {

            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* successor = min_node(node->right);
            node->data = successor->data;
            node->right = remove_node(node->right, successor->data);
        }

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = balance_factor(node);

        if (balance > 1 and balance_factor(node->left) >= 0) {
            return right_rotate(node);
        }

        if (balance < -1 and balance_factor(node->right) <= 0) {
            return left_rotate(node);
        }

        if (balance > 1 and balance_factor(node->left) < 0) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }

        if (balance < -1 and balance_factor(node->right) > 0) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        return node;
    }

    void print_tree(Node* node, int depth = 0) const {
        if (!node) return;
        print_tree(node->right, depth + 1);
        std::cout << std::string(depth * 4, ' ') << node->data << "\n";
        print_tree(node->left, depth + 1);
    }

    void in_order(Node* node) const {
        if (!node) return;
        in_order(node->left);
        std::cout << node->data << " ";
        in_order(node->right);
    }

    void delete_node(Node* node) {
        if (!node) return;
        delete_node(node->left);
        delete_node(node->right);
        delete node;
    }
};
