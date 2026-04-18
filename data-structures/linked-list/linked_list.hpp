#pragma once

#include <cstddef>

class LinkedList {
  private:
    class Node {
    public:
        int value;
        Node* next;
        Node(int val) : value(val), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t current_size = 0;

  public:
    ~LinkedList();

    /**
      * @brief Inserts a new value at the beginning of the list.
      * @param value The integer to be inserted.
      * @note Time Complexity: Θ(1)
      * @note Space Complexity: Θ(1)
      */
    void push_front(const int value);

    /**
      * @brief Inserts a new value at the end of the list.
      * @param value The integer to be inserted.
      * @note Time Complexity: Θ(1)
      * @note Space Complexity: Θ(1)
      */
    void push_back(const int value);

    /**
      * @brief Inserts a new value at the specified position.
      * @param value The integer to be inserted.
      * @param position The position to insert the element.
      * @throw std::invalid_argument If the position is out of bounds.
      * @note Time Complexity (Worst Case): O(n), where n is the list size.
      * @note Space Complexity: Θ(1)
      * @note Position = Index + 1
      */
    void insert_at(const int value, const std::size_t position);

    /**
      * @brief Removes the first element of the list, if it exists.
      * @note Time Complexity: Θ(1)
      * @note Space Complexity: Θ(1)
      */
    void pop_front();

    /**
      * @brief Removes the last element of the list, if it exists.
      * @note Time Complexity: O(n), where n is the list size.
      * @note Space Complexity: Θ(1)
      */
    void pop_back();

    /**
      * @brief Removes the element at the specified position, if it exists.
      * @param position The position of the element to remove.
      * @throw std::invalid_argument If the position is out of bounds.
      * @note Time Complexity (Worst Case): O(n), where n is the list size.
      * @note Space Complexity: Θ(1)
      * @note Position = Index + 1
      */
    void remove_at(const std::size_t position);

    /**
      * @brief Returns the current size of the list.
      * @return std::size_t The list size.
      * @note Time Complexity: Θ(1)
      * @note Space Complexity: Θ(1)
      */
    std::size_t size();

    /**
      * @brief Checks if the list is empty.
      * @return bool true if empty; false otherwise.
      * @note Time Complexity: Θ(1)
      * @note Space Complexity: Θ(1)
      */
    bool empty();

    /**
      * @brief Removes all elements from the list.
      * @note Time Complexity (Worst Case): O(n)
      * @note Space Complexity: Θ(1)
      */
    void clear();

    /**
      * @brief Reverses the order of the elements in the list.
      * @note Time Complexity (Worst Case): O(n)
      * @note Space Complexity: Θ(1)
      */
    void reverse();
};
