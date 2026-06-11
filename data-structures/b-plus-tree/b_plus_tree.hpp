#pragma once

#include <vector>

template <int T>
class BPlusTree {
public:

    BPlusTree() {
        root = new LeafNode();
    }

    ~BPlusTree() {}

    void insert(int key) {
        if (root->n == 2 * T - 1) {
            tree_root_split();
        }

        tree_insert_nonfull(root, key);
    }

    void remove(int key) {
        tree_remove(root, key);

        if (root->n == 0 and !root->is_leaf) {
            Node* old = root;
            root = static_cast<InternalNode*>(root)->children[0];
            delete old;
        }
    }

    bool search(int key) {
        Node* node = root;

        while (!node->is_leaf) {
            InternalNode* internal = static_cast<InternalNode*>(node);

            int i = 0;
            while (i < internal->n and key >= internal->keys[i]) {
                i++;
            }

            node = internal->children[i];
        }

        LeafNode* leaf = static_cast<LeafNode*>(node);

        int i = 0;
        while (i < leaf->n and key > leaf->keys[i]) {
            i++;
        }

        return i < leaf->n and key == leaf->keys[i];
    }

    std::vector<int> range(int low, int high) {
        Node* node = root;

        while (!node->is_leaf) {
            InternalNode* internal = static_cast<InternalNode*>(node);

            int i = 0;
            while (i < internal->n and low >= internal->keys[i]) {
                i++;
            }

            node = internal->children[i];
        }

        std::vector<int> result;
        LeafNode* leaf = static_cast<LeafNode*>(node);

        while (leaf != nullptr) {
            for (int i = 0; i < leaf->n; ++i) {
                if (leaf->keys[i] > high) {
                    return result;
                }
                if (leaf->keys[i] >= low) {
                    result.push_back(leaf->keys[i]);
                }
            }

            leaf = leaf->next;
        }

        return result;
    }

private:

    struct Node {
        int keys[2 * T - 1];
        int n;
        bool is_leaf;
    };

    struct InternalNode : Node {
        Node* children[2 * T];

        InternalNode() {
            for (auto &c : children) {
                c = nullptr;
            }

            this->is_leaf = false;
        }
    };

    struct LeafNode : Node {
        LeafNode* next = nullptr;

        LeafNode() {
            this->is_leaf = true;
        }
    };

    Node* root;

    void tree_insert_nonfull(Node* node, int key) {
        int i = node->n - 1;

        if (node->is_leaf) {
            while (i >= 0 and key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }

            node->keys[i + 1] = key;
            node->n++;

            return;
        }

        InternalNode* internal = static_cast<InternalNode*>(node);

        while (i >= 0 and key < internal->keys[i]) {
            i--;
        }
        i++;

        if (internal->children[i]->n == 2 * T - 1) {

            if (internal->children[i]->is_leaf) {
                tree_leaf_split(internal, i);
            } else {
                tree_internal_split(internal, i);
            }

            if (key > node->keys[i]) {
                i++;
            }
        }

        tree_insert_nonfull(internal->children[i], key);
    }

    void tree_remove(Node* node, int key) {
        int i = 0;

        if (node->is_leaf) {
            LeafNode* leaf = static_cast<LeafNode*>(node);

            while (i < leaf->n and key > leaf->keys[i]) {
                i++;
            }

            if (i >= leaf->n or key != leaf->keys[i]) {
                return;
            }

            for (int j = i; j < leaf->n - 1; ++j) {
                leaf->keys[j] = leaf->keys[j + 1];
            }
            leaf->n--;

            return;
        }

        InternalNode* internal = static_cast<InternalNode*>(node);

        while (i < internal->n and key >= internal->keys[i]) {
            i++;
        }

        if (internal->children[i]->n <= T - 1) {
            tree_ensure_min_keys(internal, i);

            i = 0;
            while (i < internal->n and key >= internal->keys[i]) {
                i++;
            }
        }

        tree_remove(internal->children[i], key);
    }

    void tree_internal_split(InternalNode* parent, int idx) {
        InternalNode* left = static_cast<InternalNode*>(parent->children[idx]);
        InternalNode* right = new InternalNode();

        right->n = T - 1;

        for (int i = 0; i < T - 1; ++i) {
            right->keys[i] = left->keys[T + i];
        }

        for (int i = 0; i < T; ++i) {
            right->children[i] = left->children[T + i];
        }

        left->n = T - 1;

        for (int i = parent->n; i >= idx; --i) {
            parent->children[i + 1] = parent->children[i];
        }
        parent->children[idx + 1] = right;

        for (int i = parent->n - 1; i>= idx; --i) {
            parent->keys[i + 1] = parent->keys[i];
        }
        parent->keys[idx] = left->keys[T - 1];

        parent->n++;
    }

    LeafNode* tree_leaf_split(InternalNode* parent, int idx) {
        LeafNode* left = static_cast<LeafNode*>(parent->children[idx]);
        LeafNode* right = new LeafNode();

        right->n = T - 1;
        for (int i = 0; i < T - 1; ++i) {
            right->keys[i] = left->keys[T + i];
        }

        left->n = T;

        right->next = left->next;
        left->next = right;

        for (int i = parent->n; i >= idx; --i) {
            parent->children[i + 1] = parent->children[i];
        }
        parent->children[idx + 1] = right;

        for (int i = parent->n - 1; i>= idx; --i) {
            parent->keys[i + 1] = parent->keys[i];
        }
        parent->keys[idx] = right->keys[0];

        parent->n++;
        return right;
    }

    void tree_root_split() {
        if (root->is_leaf) {
            LeafNode* old_root = static_cast<LeafNode*>(root);
            InternalNode* new_root = new InternalNode();

            new_root->children[0] = old_root;
            root = new_root;

            tree_leaf_split(new_root, 0);
        } else {
            InternalNode* new_root = new InternalNode();

            new_root->children[0] = root;
            root = new_root;

            tree_internal_split(new_root, 0);
        }
    }

    void tree_rotate_right(InternalNode* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx - 1];

        if (child->is_leaf) {
            LeafNode* leaf_child = static_cast<LeafNode*>(child);
            LeafNode* leaf_sibling = static_cast<LeafNode*>(sibling);

            for (int i = leaf_child->n; i > 0; --i)
                leaf_child->keys[i] = leaf_child->keys[i - 1];

            leaf_child->keys[0] = leaf_sibling->keys[leaf_sibling->n - 1];
            leaf_child->n++;
            leaf_sibling->n--;

            node->keys[idx - 1] = leaf_child->keys[0];
        } else {
            InternalNode* internal_child = static_cast<InternalNode*>(child);
            InternalNode* internal_sibling = static_cast<InternalNode*>(sibling);

            for (int i = internal_child->n; i > 0; --i)
                internal_child->keys[i] = internal_child->keys[i - 1];
            for (int i = internal_child->n + 1; i > 0; --i)
                internal_child->children[i] = internal_child->children[i - 1];

            internal_child->keys[0] = node->keys[idx - 1];
            internal_child->children[0] = internal_sibling->children[internal_sibling->n];
            internal_child->n++;

            node->keys[idx - 1] = internal_sibling->keys[internal_sibling->n - 1];
            internal_sibling->n--;
        }
    }

    void tree_rotate_left(InternalNode* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx + 1];

        if (child->is_leaf) {
            LeafNode* leaf_child = static_cast<LeafNode*>(child);
            LeafNode* leaf_sibling = static_cast<LeafNode*>(sibling);

            leaf_child->keys[leaf_child->n] = leaf_sibling->keys[0];
            leaf_child->n++;

            for (int i = 0; i < leaf_sibling->n - 1; ++i)
                leaf_sibling->keys[i] = leaf_sibling->keys[i + 1];
            leaf_sibling->n--;

            node->keys[idx] = leaf_sibling->keys[0];
        } else {
            InternalNode* internal_child = static_cast<InternalNode*>(child);
            InternalNode* internal_sibling = static_cast<InternalNode*>(sibling);

            internal_child->keys[internal_child->n] = node->keys[idx];
            internal_child->children[internal_child->n + 1] = internal_sibling->children[0];
            internal_child->n++;

            node->keys[idx] = internal_sibling->keys[0];

            for (int i = 0; i < internal_sibling->n - 1; ++i)
                internal_sibling->keys[i] = internal_sibling->keys[i + 1];
            for (int i = 0; i < internal_sibling->n; ++i)
                internal_sibling->children[i] = internal_sibling->children[i + 1];
            internal_sibling->n--;
        }
    }

    void tree_merge_children(InternalNode* node, int idx) {
        Node* left = node->children[idx];
        Node* right = node->children[idx + 1];

        if (left->is_leaf) {
            LeafNode* leaf_left = static_cast<LeafNode*>(left);
            LeafNode* leaf_right = static_cast<LeafNode*>(right);

            for (int i = 0; i < leaf_right->n; ++i)
                leaf_left->keys[leaf_left->n + i] = leaf_right->keys[i];
            leaf_left->n += leaf_right->n;
            leaf_left->next = leaf_right->next;

            delete leaf_right;
        } else {
            InternalNode* internal_left = static_cast<InternalNode*>(left);
            InternalNode* internal_right = static_cast<InternalNode*>(right);

            internal_left->keys[internal_left->n] = node->keys[idx];
            for (int i = 0; i < internal_right->n; ++i)
                internal_left->keys[internal_left->n + 1 + i] = internal_right->keys[i];
            for (int i = 0; i <= internal_right->n; ++i)
                internal_left->children[internal_left->n + 1 + i] = internal_right->children[i];
            internal_left->n += internal_right->n + 1;

            delete internal_right;
        }

        for (int i = idx; i < node->n - 1; ++i) {
            node->keys[i] = node->keys[i + 1];
            node->children[i + 1] = node->children[i + 2];
        }
        node->n--;
    }

    void tree_ensure_min_keys(InternalNode* node, int idx) {
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
};
