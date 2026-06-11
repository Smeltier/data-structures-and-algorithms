#pragma once

#include <cstddef>
#include <utility>

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
        tree_remove(root, key);

        if (root->n == 0 and !root->is_leaf) {
            Node* old = root;
            root = root->children[0];
            delete old;
        }
    }

    bool search(int key) const {
        if (root == nullptr) {
            return false;
        }
        auto [node, idx] = tree_search(root, key);
        return node != nullptr;
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

    void tree_insert_nonfull(Node *node, int k) {
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
        Node *new_root = new Node(false);

        new_root->children[0] = root;

        root = new_root;

        tree_child_split(new_root, 0);

        return new_root;
    }

    void tree_merge_children(Node *node, int idx) {
        Node *left = node->children[idx];
        Node *right = node->children[idx + 1];

        left->keys[T - 1] = node->keys[idx];

        for (int i = 0; i < right->n; ++i) {
            left->keys[T + i] = right->keys[i];
        }

        if (!left->is_leaf) {
            for (int i = 0; i <= right->n; ++i) {
                left->children[T + i] = right->children[i];
            }
        }

        left->n = 2 * T - 1;

        for (int i = idx; i < node->n - 1; ++i) {
            node->keys[i] = node->keys[i + 1];
            node->children[i + 1] = node->children[i + 2];
        }

        node->n--;

        delete right;
    }

    int tree_predecessor(Node *node) {
        while (!node->is_leaf) {
            node = node->children[node->n];
        }

        return node->keys[node->n - 1];
    }

    int tree_successor(Node *node) {
        while (!node->is_leaf) {
            node = node->children[0];
        }

        return node->keys[0];
    }

    void tree_rotate_right(Node *node, int idx) {
        Node *child = node->children[idx];
        Node *sibling = node->children[idx - 1];

        for (int i = child->n; i > 0; --i) {
            child->keys[i] = child->keys[i - 1];
        }

        if (!child->is_leaf) {
            for (int i = child->n + 1; i > 0; --i) {
                child->children[i] = child->children[i - 1];
            }

            child->children[0] = sibling->children[sibling->n];
        }

        child->keys[0] = node->keys[idx - 1];
        node->keys[idx - 1] = sibling->keys[sibling->n - 1];

        child->n++;
        sibling->n--;
    }

    void tree_rotate_left(Node *node, int idx) {
        Node *child = node->children[idx];
        Node *sibling = node->children[idx + 1];

        child->keys[child->n] = node->keys[idx];

        if (!child->is_leaf) {
            child->children[child->n + 1] = sibling->children[0];
        }

        node->keys[idx] = sibling->keys[0];

        for (int i = 0; i < sibling->n - 1; ++i) {
            sibling->keys[i] = sibling->keys[i + 1];
        }

        if (!sibling->is_leaf) {
            for (int i = 0; i < sibling->n; ++i) {
                sibling->children[i] = sibling->children[i + 1];
            }
        }

        child->n++;
        sibling->n--;
    }

    void tree_ensure_min_keys(Node *node, int idx) {
        if (idx > 0 and node->children[idx - 1]->n >= T) {
            tree_rotate_right(node, idx);
        } else if (idx < node->n and node->children[idx + 1]->n >= T) {
            tree_rotate_left(node, idx);
        } else {
            if (idx < node->n) {
                tree_merge_children(node, idx);
            } else {
                tree_merge_children(node, idx - 1);
            }
        }
    }

    void tree_remove(Node *node, int key) {
        int i = 0;

        while (i < node->n and key > node->keys[i]) {
            i++;
        }

        if (i < node->n and key == node->keys[i]) {
            if (node->is_leaf) {
                for (int j = i; j < node->n - 1; ++j) {
                    node->keys[j] = node->keys[j + 1];
                }

                node->n--;
            } else if (node->children[i]->n >= T) {
                int pred = tree_predecessor(node->children[i]);
                node->keys[i] = pred;
                tree_remove(node->children[i], pred);
            } else if (node->children[i + 1]->n >= T) {
                int succ = tree_successor(node->children[i + 1]);
                node->keys[i] = succ;
                tree_remove(node->children[i + 1], succ);
            } else {
                tree_merge_children(node, i);
                tree_remove(node->children[i], key);
            }
        } else {
            if (node->is_leaf) {
                return;
            }

            bool last = (i == node->n);

            if (node->children[i]->n < T) {
                tree_ensure_min_keys(node, i);

                if (last and i > node->n) {
                    i--;
                }
            }

            tree_remove(node->children[i], key);
        }
    }
};
