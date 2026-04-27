#pragma once

#include <cstddef>

class LinkedStack {
  private:
    class Node {
      public:
        int value;
        Node* next;
        Node(int val) : value(val), next(nullptr) {}
    };

    Node* head = nullptr;
    std::size_t current_size = 0;

  public:
    ~LinkedStack();

    /**
      * @brief Inserts a new value at the beginning of the stack.
      * @param value The integer to be inserted.
      * @note Time Complexity: Θ(1)
      * @note Space Complexity: Θ(1)
      */
    void push(const int value);

    /**
      * @brief Removes an element from the stack.
      * @note Time Complexity: Θ(1)
      * @note Space Complexity: Θ(1)
      */
    void pop();

    /**
      * @brief Return the element in the top of the stack.
      * @retrun int The element in the top.
      * @note Time Complexity: Θ(1)
      * @note Space Complexity: Θ(1)
      */
    int top() const;

    /**
      * @brief Returns the current size of the stack.
      * @return std::size_t The list size.
      * @note Time Complexity: Θ(1)
      * @note Space Complexity: Θ(1)
      */
    std::size_t size() const;

    /**
      * @brief Checks if the stack is empty.
      * @return bool true if empty; false otherwise.
      * @note Time Complexity: Θ(1)
      * @note Space Complexity: Θ(1)
      */
    bool empty() const;

    /**
      * @brief Removes all elements from the stack.
      * @note Time Complexity (Worst Case): O(n)
      * @note Space Complexity: Θ(1)
      */
    void clear();
};
