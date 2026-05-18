#include <iostream>

#include "hash_table.hpp"

HashTable::HashTable() : table(0, -1), current_size(0) {}

HashTable::HashTable(const size_t size) : table(size, -1), current_size(0) {}

int HashTable::hash(const int key) const {
  return (key) % (int)table.size();
}

void HashTable::insert(const int key) {
  if (full()) {
    return;
  }

  int start_index = hash(key);
  int index = start_index;

  for (size_t i = 0; i < (int)table.size(); ++i) {
    if (table[index] == -1) {
      table[index] = key;
      current_size++;
      return;
    }

    index = (index + 1) % (int)table.size();
  }
}

void HashTable::remove(const int key) {
  if (empty()) {
    return;
  }

  int index = hash(key);

  for (size_t i = 0; i < (int)table.size(); ++i) {
    if (table[index] == key) {
      table[index] = -1;
      current_size--;
      return;
    }

    index = (index + 1) % (int)table.size();
  }
}

bool HashTable::search(const int key) const {
  if (empty()) {
    return false;
  }

  int index = hash(key);

  for (size_t i = 0; i < (int)table.size(); ++i) {
    if (table[index] == key) {
      return true;
    }
    index = (index + 1) % (int)table.size();
  }

  return false;
}

void HashTable::print() const {
  for (int element : table) {
    if (element == -1) {
      std::cout << "_ ";
    }
    else {
      std::cout << element << " ";
    }
  }
}

size_t HashTable::max_size() const {
  return table.size();
}

size_t HashTable::size() const {
  return current_size;
}

bool HashTable::empty() const {
  return current_size == 0;
}

bool HashTable::full() const {
  return current_size == table.size();
}
