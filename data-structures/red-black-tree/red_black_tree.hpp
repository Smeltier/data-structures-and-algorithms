#pragma once

#include <iostream>

class RedBlackTree {
private:

    enum class Color {
        RED,
        BLACK,
    };

    struct Node {
        int value;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* father = nullptr;
        Color color = Color::RED;

        Node(int value) : value(value) {}
    };

    Node* root = nullptr;

    void remove(Node* z) {
        Node* x = nullptr;
        Node* y = z;
        Color y_base_color = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_base_color = y->color;
            x = y->right;

            if (y != z->right) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->father = y;
            } else if (x != nullptr) {
                x->father = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->father = y;
            y->color = z->color;
        }

        if (y_base_color == Color::BLACK) {
            fix_remove(x);
        }
    }

    Node* minimum(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void fix_remove(Node* x) {
        while (x != nullptr and x != this->root and x->color == Color::BLACK) {
            Node* w = nullptr;

            if (x == x->father->left) {
                w = x->father->right;

                if (w != nullptr and w->color == Color::RED) {
                    w->color = Color::BLACK;
                    x->father->color = Color::RED;
                    left_rotate(x->father);
                    w = x->father->right;
                }

                bool left_black = (w == nullptr or w->left == nullptr or w->left->color == Color::BLACK);
                bool right_black = (w == nullptr or w->right == nullptr or w->right->color == Color::BLACK);

                if (w != nullptr and left_black and right_black) {
                    w->color = Color::RED;
                    x = x->father;
                } else {
                    if (w->right == nullptr or w->right->color == Color::BLACK) {
                        if (w->left != nullptr) {
                            w->left->color = Color::BLACK;
                        }

                        w->color = Color::RED;
                        right_rotate(w);
                        w = x->father->right;
                    }

                    w->color = x->father->color;
                    x->father->color = Color::BLACK;

                    if (w->right != nullptr) {
                        w->right->color = Color::BLACK;
                    }

                    left_rotate(x->father);
                    x = this->root;
                }
            } else {
                w = x->father->left;

                if (w != nullptr and w->color == Color::RED) {
                    w->color = Color::BLACK;
                    x->father->color = Color::RED;
                    right_rotate(x->father);
                    w = x->father->left;
                }

                bool left_black = (w == nullptr or w->left == nullptr or w->left->color == Color::BLACK);
                bool right_black = (w == nullptr or w->right == nullptr or w->right->color == Color::BLACK);

                if (w != nullptr and left_black and right_black) {
                    w->color = Color::RED;
                    x = x->father;
                } else {
                    if (w->left == nullptr or w->left->color == Color::BLACK) {
                        if (w->right != nullptr) {
                            w->right->color = Color::BLACK;
                        }

                        w->color = Color::RED;
                        left_rotate(w);
                        w = x->father->left;
                    }

                    w->color = x->father->color;
                    x->father->color = Color::BLACK;

                    if (w->left != nullptr) {
                        w->left->color = Color::BLACK;
                    }

                    right_rotate(x->father);
                    x = this->root;
                }
            }
        }

        x->color = Color::BLACK;
    }

    void fix_insert(Node* z) {
        while (z -> father != nullptr and z->father->color == Color::RED) {
            Node* y = nullptr;

            if (z->father == z->father->father->left) {
                y = z->father->father->right;

                if (y != nullptr and y->color == Color::RED) {
                    z->father->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->father->father->color = Color::RED;
                    z = z->father->father;
                } else {

                    if (z == z->father->right) {
                        z = z->father;
                        left_rotate(z);
                    }

                    z->father->color = Color::BLACK;
                    z->father->father->color = Color::RED;

                    right_rotate(z->father->father);
                }
            } else {
                y = z->father->father->left;

                if (y != nullptr and y->color == Color::RED) {
                    z->father->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->father->father->color = Color::RED;
                    z = z->father->father;
                } else {

                    if (z == z->father->left) {
                        z = z->father;
                         right_rotate(z);
                    }

                    z->father->color = Color::BLACK;
                    z->father->father->color = Color::RED;

                    left_rotate(z->father->father);
                }
            }
        }

        this->root->color = Color::BLACK;
    }

    void left_rotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->father = x;
        }
        y->father = x->father;

        if (x->father == nullptr) {
            this->root = y;
        } else if (x == x->father->left) {
            x->father->left = y;
        } else {
            x->father->right = y;
        }

        y->left = x;
        x->father = y;
    }

    void right_rotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nullptr) {
            x->right->father = y;
        }
        x->father = y->father;

        if (y->father == nullptr) {
            this->root = x;
        } else if (y == y->father->right) {
            y->father->right = x;
        } else {
            y->father->left = x;
        }

        x->right = y;
        y->father = x;
    }

    void transplant(Node* u, Node* v) {
        if (u->father == nullptr) {
            this->root = v;
        } else if (u == u->father->left) {
            u->father->left = v;
        } else {
            u->father->right = v;
        }

        if (v != nullptr) {
            v->father = u->father;
        }
    }

    int black_height(Node* node) const {
        if (node == nullptr) {
            return 1;
        }

        int left = black_height(node->left);
        int right = black_height(node->right);

        if (left == -1 || right == -1 || left != right) {
            return -1;
        }

        return (node->color == Color::BLACK) ? left + 1 : left;
    }

    void in_order(Node* node) const {
        if (node == nullptr) {
            return;
        }

        in_order(node->left);
        std::cout << node->value << " ";
        in_order(node->right);
    }

public:

    void insert(int value) {
        Node* x = this->root;
        Node* y = nullptr;

        while (x != nullptr) {
            y = x;

            if (value < x->value) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        Node* z = new Node(value);

        z->father = y;

        if (y == nullptr) {
            this->root = z;
        } else if (z->value < y->value) {
            y->left = z;
        } else {
            y->right = z;
        }

        fix_insert(z);
    }

    void remove(int value) {
        Node* x = this->root;

        while (x != nullptr) {
            if (value == x->value) {
                remove(x);
                return;
            } else if (value < x->value) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
    }

    void print() const {
        in_order(this->root);
    }
};
