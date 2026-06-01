#pragma once

#include <cstddef>
#include <stdexcept>

template <typename value_type>
class LinkedList {
private:

    struct Node {
        value_type value;
        Node* next;

        Node(const value_type value) : value(value), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t current_size = 0;

public:

    LinkedList() {}

    ~LinkedList() {
        clear();
    }

    /**
     * @brief Inserts a new value at the beginning of the list.
     * @param value The integer to be inserted.
     * @note Time Complexity: Θ(1)
     * @note Space Complexity: Θ(1)
     */
    void push_front(const value_type value) {
        Node* new_node = new Node(value);

        new_node->next = head;
        head = new_node;

        if (current_size == 0) {
            tail = new_node;
        }

        current_size++;
    }

    /**
     * @brief Inserts a new value at the end of the list.
     * @param value The integer to be inserted.
     * @note Time Complexity: Θ(1)
     * @note Space Complexity: Θ(1)
     */
    void push_back(const value_type value) {
        Node* new_node = new Node(value);

        if (head == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        current_size++;
    }

    /**
     * @brief Inserts a new value at the specified position.
     * @param value The integer to be inserted.
     * @param position The position to insert the element.
     * @throw std::invalid_argument If the position is out of bounds.
     * @note Time Complexity (Worst Case): O(n), where n is the list size.
     * @note Space Complexity: Θ(1)
     * @note Position = Index + 1
     */
    void insert_at(const value_type value, const std::size_t position) {
        if (position < 1 || position > current_size + 1) {
            throw std::invalid_argument("Invalid position.");
        }

        if (position == 1) {
            push_front(value);
            return;
        }
        if (position == current_size + 1) {
            push_back(value);
            return;
        }

        Node* previous = head;
        for (std::size_t i = 1; i < position - 1; ++i) {
            previous = previous->next;
        }

        Node* new_node = new Node(value);
        new_node->next = previous->next;
        previous->next = new_node;
        current_size++;
    }

    /**
     * @brief Removes the first element of the list, if it exists.
     * @note Time Complexity: Θ(1)
     * @note Space Complexity: Θ(1)
     */
    void pop_front() {
        if (empty()) {
            return;
        }

        Node* to_delete = head;
        head = head->next;

        if (!head) {
            tail = nullptr;
        }

        delete to_delete;
        current_size--;
    }

    /**
     * @brief Removes the last element of the list, if it exists.
     * @note Time Complexity: O(n), where n is the list size.
     * @note Space Complexity: Θ(1)
     */
    void pop_back() {
        if (empty()) {
            return;
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* prev = head;
            while (prev->next != tail) {
                prev = prev->next;
            }

            delete tail;
            tail = prev;

            tail->next = nullptr;
        }

        current_size--;
    }

    /**
     * @brief Removes the element at the specified position, if it exists.
     * @param position The position of the element to remove.
     * @throw std::invalid_argument If the position is out of bounds.
     * @note Time Complexity (Worst Case): O(n), where n is the list size.
     * @note Space Complexity: Θ(1)
     * @note Position = Index + 1
     */
    void remove_at(const std::size_t position) {
        if (position < 1 || position > current_size) {
            throw std::invalid_argument("Invalid position.");
        }

        if (position == 1) {
            pop_front();
            return;
        }
        if (position == current_size) {
            pop_back();
            return;
        }

        Node* prev = head;
        for (std::size_t i = 1; i < position - 1; ++i) {
            prev = prev->next;
        }

        Node* to_delete = prev->next;
        prev->next = to_delete->next;

        delete to_delete;
        current_size--;
    }

    /**
     * @brief Returns the element at the beginning of the list.
     * @return value_type the element at the front of the list.
     * @throw std::runtime_error If the method is called on an empty list.
     */
    value_type front() const {
        if (empty()) {
            throw std::runtime_error("Cannot return the front element of an empty list.");
        }

        return head->value;
    }

    /**
     * @brief Returns the element at the end of the list.
     * @return value_type the element at the end of the list.
     * @throw std::runtime_error If the method is called for a list with size less than or equal to one.
     */
    value_type back() const {
        if (size() <= 1) {
            throw std::runtime_error("Cannot return the back element of a list of size less than or equal to one.");
        }

        return tail->value;
    }

    /**
     * @brief Returns the current size of the list.
     * @return std::size_t The list size.
     * @note Time Complexity: Θ(1)
     * @note Space Complexity: Θ(1)
     */
    std::size_t size() const {
        return current_size;
    }

    /**
     * @brief Checks if the list is empty.
     * @return bool true if empty; false otherwise.
     * @note Time Complexity: Θ(1)
     * @note Space Complexity: Θ(1)
     */
    bool empty() const {
        return current_size == 0;
    }

    /**
     * @brief Removes all elements from the list.
     * @note Time Complexity (Worst Case): O(n)
     * @note Space Complexity: Θ(1)
     */
    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }

        head = tail = nullptr;
        current_size = 0;
    }

    /**
     * @brief Reverses the order of the elements in the list.
     * @note Time Complexity (Worst Case): O(n)
     * @note Space Complexity: Θ(1)
     */
    void reverse() {
        if (!head || !head->next) {
            return;
        }

        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        tail = head;

        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;
    }
};
