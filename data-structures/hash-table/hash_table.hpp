#pragma once

#include <vector>

class HashTable {
private:
  std::vector<int> table;
  size_t current_size;

  int hash(const int key) const;

public:
  HashTable();

  HashTable(const size_t size);

  void insert(const int key);

  void remove(const int key);

  bool search(const int key) const;

  void print() const;

  size_t max_size() const;

  size_t size() const;

  bool empty() const;

  bool full() const;
};
