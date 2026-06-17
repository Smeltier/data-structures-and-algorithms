#include <iostream>

#include "avl_tree.hpp"

int main (int argc, char *argv[]) {
    AVLTree tree;

    for (int i = 1; i <= 10; ++i) {
        std::cout << "Inserindo o " << i << std::endl;
        tree.insert(i);

        std::cout << std::endl;
        tree.print();
        std::cout << std::endl;
    }

    for (int i = 1; i <= 10; ++i) {
        std::cout << "Removendo o " << i << std::endl;
        tree.remove(i);

        std::cout << std::endl;
        tree.print();
        std::cout << std::endl;
    }

    return 0;
}
