#include <iostream>

#include "hash_table.hpp"

int main (int argc, char *argv[]) {
  HashTable map(13);

  map.print();
  std::cout << std::endl;


  map.insert(13);
  map.print();
  std::cout << std::endl;

  map.insert(17);
  map.print();
  std::cout << std::endl;

  if (map.search(17)) {
    std::cout << "ACHOU!" << std::endl;
  }
  else {
    std::cout << "NÃO ACHOU!" << std::endl;
  }

  map.remove(17);
  map.print();
  std::cout << std::endl;

  if (map.search(17)) {
    std::cout << "ACHOU!" << std::endl;
  }
  else {
    std::cout << "NÃO ACHOU!" << std::endl;
  }
  
  return 0;
}
