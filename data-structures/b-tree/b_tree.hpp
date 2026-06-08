#pragma once

#include <cstddef>
#include <utility>
#include <iostream>

template <int T>
class BTree {
public:

    BTree() {
        root = new Node(true);
    }

    ~BTree() {}

    void insert(int key) {
        if (root->n == 2 * T - 1) {
            Node* s = tree_root_split();
            tree_insert_nonfull(s, key);
        } else {
            tree_insert_nonfull(root, key);
        }
    }

    void remove(int key) {
    }

    bool search(int key) {
        if (root == nullptr) {
            return false;
        }
        auto [node, idx] = tree_search(root, key);
        return node != nullptr;
    }

    void print_root() {
        print_tree(root);
    }


private:

    struct Node {
        int keys[2 * T - 1];
        Node *children[2 * T];
        int n;
        bool is_leaf;

        Node(bool is_leaf) : is_leaf(is_leaf), n(0) {
            for (std::size_t i = 0; i < 2 * T; ++i) {
                children[i] = nullptr;
            }
        }
    };

    Node* root;

    // void print_tree(Node* node, int depth = 0) {
    //     for (int i = 0; i < depth; i++) std::cout << "  ";
    //     for (int i = 0; i < node->n; i++) std::cout << node->keys[i] << " ";
    //     std::cout << "\n";
    //     if (!node->is_leaf)
    //         for (int i = 0; i <= node->n; i++)
    //             print_tree(node->children[i], depth + 1);
    // }

    void tree_insert_nonfull(Node* node, int k) {
        int i = node->n - 1;

        if (node->is_leaf) {

            while (i >= 0 and k < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }

            node->keys[i + 1] = k;
            node->n++;

            return;
        }

        while (i >= 0 and k < node->keys[i]) {
            i--;
        }
        i++;

        if (node->children[i]->n == 2 * T - 1) {
            tree_child_split(node, i);

            if (k > node->keys[i]) {
                i++;
            }
        }

        tree_insert_nonfull(node->children[i], k);
    }

    std::pair<Node*, int> tree_search(Node *node, int k) {
        int it = 0;
        while (it < node->n and k > node->keys[it]) {
            it++;
        }

        if (it < node->n and k == node->keys[it]) {
            return {node, it};
        }

        if (node->is_leaf) {
            return {nullptr, -1};
        }

        return tree_search(node->children[it], k);
    }

    // Θ(T)
    void tree_child_split(Node *node, int idx) {
        Node* full = node->children[idx];

        Node* new_leaf = new Node(full->is_leaf);
        new_leaf->n = T - 1;

        for (int j = 0; j < T - 1; ++j) {
            new_leaf->keys[j] = full->keys[T + j];
        }

        if (!full->is_leaf) {
            for (int j = 0; j < T; ++j) {
                new_leaf->children[j] = full->children[T + j];
            }
        }

        full->n = T - 1;

        for (int j = node->n; j >= idx; --j) {
            node->children[j + 1] = node->children[j];
        }
        node->children[idx + 1] = new_leaf;

        for (int j = node->n - 1; j >= idx; --j) {
            node->keys[j + 1] = node->keys[j];
        }
        node->keys[idx] = full->keys[T - 1];

        node->n++;
    }

    // Θ(T)
    Node* tree_root_split() {
        Node* new_root = new Node(false);

        new_root->children[0] = root;

        root = new_root;

        tree_child_split(new_root, 0);

        return new_root;
    }
};
