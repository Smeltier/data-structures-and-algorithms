#include <cstddef>

#include "linked_stack.hpp"

LinkedStack::~LinkedStack() {
  clear();
}

void LinkedStack::push(const int value) {
  Node* new_node = new Node(value);

  new_node->next = head->next;
  head = new_node;

  current_size++;
}

void LinkedStack::pop() {
  if (!head) return;

  Node* to_delete = head;
  head = head->next;

  delete to_delete;
  current_size--;
}

int LinkedStack::top() const {
  return head->value;
}

bool LinkedStack::empty() const {
  return current_size == 0;
}

std::size_t LinkedStack::size() const {
  return current_size;
}

void LinkedStack::clear() {
  Node* current = head;
  while (current) {
    Node* remove = current;
    current = current->next;
    delete remove;
  }

  head = nullptr;
  current_size = 0;
}
