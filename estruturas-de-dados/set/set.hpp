#pragma once

#include <utility>
#include <vector>

/*
 * @details Define uma estrutura de dados do tipo Set, onde os elementos internos permanecem ordenados e duplicatas não são permitidas.
 *
 * */
template<typename T>
class Set {

public: 

  /*
   * @brief Adiciona um elemento no conjunto caso ele ainda não exista.
   *
   * @param value O elemento que será inserido.
   *
   * @note Complexidade de Tempo: O(n) no pior caso, sendo n o tamanho do conjunto.
   *
   * */
  void add(const T& value) {
    if (contains(value)) {
      return;
    }

    elements.push_back(value);
    elements_size++;

    for (size_t it = elements_size - 1; it > 0; --it) {
      if (elements[it] < elements[it - 1]) {
        std::swap(elements[it], elements[it - 1]);
      }
      else {
        break;
      }
    }
  }

  /*
   * @brief Remove um elemento do conjunto.
   *
   * @param value O elemento que será removido.
   *
   * @note Complexidade de Tempo: O(n) no pior caso, sendo n o tamanho do conjunto.
   *
   * */
  void remove(const T& value) {
    int position = search(value);
    if (position == 0) {
      return;
    }

    elements.erase(elements.begin() + (position - 1));
    elements_size--;
  }

  /*
   * @brief Limpa todo o conjunto, removendo os elementos.
   *
   * @note Complexidade de Tempo: O(n) no pior caso, sendo n o tamanho do conjunto.
   *
   * */
  void clear() {
    elements.clear();
    elements_size = 0;
  }

  /*
   * @brief verifica se o conjunto contém determinado elemento.
   * 
   * @param value o elemento que queremos verificar.
   *
   * @return true se o elemento estiver presente no conjunto; false caso contrário.
   *
   * @note Complexidade de tempo: O(log n) no pior caso, sendo n o tamanho do conjunto.
   *
   * */
  bool contains(const T& value) const {
    return search(value) != 0;
  }

  /*
   * @brief Verifica se o conjunto está vazio.
   *
   * @return true caso esteja vazio; false caso contrário.
   *
   * @note Complexidade de tempo: O(1).
   *
   * */
  bool empty() const {
    return elements_size == 0;
  }

  /*
   * @brief Tamanho atual do conjunto, ou seja, quantidade de elementos presente nele.
   *
   * */
  size_t size() const {
    return elements_size;
  }

  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

  iterator begin() {
    return elements.begin();
  }

  iterator end() {
    return elements.end();
  }

  const_iterator begin() const {
    return elements.begin();
  }

  const_iterator end() const {
    return elements.end();
  }

private:

  std::vector<T> elements;
  size_t elements_size = 0;
  
  /*
   * @brief Procura determinado elemento no conjunto e retorna sua posição, caso presente.
   * 
   * @param value o elemento que queremos encontrar.
   *
   * @return Posição do elemento no conjunto; 0 caso não esteja presente.
   *
   * @note Complexidade de tempo: O(log n) no pior caso, sendo n o tamanho do conjunto.
   *
   * */
  int search(const T& value) const {
    int left = 0;
    int right = static_cast<int>(elements_size) - 1;

    while (left <= right) {
      int middle = left + (right - left) / 2;

      if (value == elements[middle]) {
        return middle + 1;
      }
      else if (value < elements[middle]) {
        right = middle - 1;
      }
      else {
        left = middle + 1;
      }
    }

    return 0;
  }
};
