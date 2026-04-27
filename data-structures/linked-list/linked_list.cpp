#include <stdexcept>

#include "linked_list.hpp"

LinkedList::~LinkedList() {
  clear();
}

void LinkedList::push_front(const int value) {
  Node* new_node = new Node(value);
  new_node->next = head;
  head = new_node;
  if (current_size == 0) tail = new_node;
  current_size++;
}

void LinkedList::push_back(const int value) {
  Node* new_node = new Node(value);
  if (head == nullptr) {
    head = tail = new_node;
  } else {
    tail->next = new_node;
    tail = new_node;
  }
  current_size++;
}

void LinkedList::insert_at(const int value, const std::size_t position) {
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

void LinkedList::pop_front() {
  if (!head) return;

  Node* to_delete = head;
  head = head->next;

  if (!head) tail = nullptr;

  delete to_delete;
  current_size--;
}

void LinkedList::pop_back() {
  if (!head) return;

  if (head == tail) {
    delete head;
    head = tail = nullptr;
  }
  else {
    Node* prev = head;
    while (prev->next != tail) prev = prev->next;
    delete tail;
    tail = prev;
    tail->next = nullptr;
  }
  current_size--;
}

void LinkedList::remove_at(const std::size_t position) {
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

std::size_t LinkedList::size() { 
  return current_size; 
}

bool LinkedList::empty() { 
  return current_size == 0; 
}

void LinkedList::clear() {
  Node* current = head;
  while (current) {
    Node* next = current->next;
    delete current;
    current = next;
  }

  head = tail = nullptr;
  current_size = 0;
}

void LinkedList::reverse() {
  if (!head || !head->next) return;

  Node *prev = nullptr, *curr = head, *next = nullptr;
  tail = head;

  while (curr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  head = prev;
}
