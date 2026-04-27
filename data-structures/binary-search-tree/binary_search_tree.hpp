#pragma once

class BinarySearchTree {
  private:
    class Node {
      int value;
      Node* left;
      Node* right;
      Node(const int value) : value(value), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

  public:
    ~BinarySearchTree();

    void insert(const int value);
    
    void remove(const int value);

    bool search(const int value) const;
};
