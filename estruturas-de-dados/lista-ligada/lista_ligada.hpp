#pragma once

#include <cstddef>

class ListaLigada {
private:
  class No {
  public:
    int valor;
    No* proximo;
    No(int valor) : valor(valor), proximo(nullptr) {}
  };

  No* principal = nullptr;
  No* cauda = nullptr;
  size_t tamanho_atual = 0;

public:
  ~ListaLigada();

  /**
   * @brief Insere um novo valor no início da lista ligada.
   * @param valor O número inteiro que será inserido
   * @note Complexidade de Tempo: Θ(1)
   * @note Complexidade de Espaço: Θ(1)
   */
  void inserir_inicio(const int valor);

  /**
   * @brief Insere um novo valor no fim da lista ligada.
   * @param valor O número inteiro que será inserido
   * @note Complexidade de Tempo: Θ(1)
   * @note Complexidade de Espaço: Θ(1)
   */
  void inserir_fim(const int valor);

  /**
   * @brief Insere um novo valor na posição escolhida.
   * @param valor O número inteiro que será inserido
   * @param posicao A posição que o elemento será inserido
   * @throw std::invalid_argument Se a posição for fora dos limites.
   * @note Complexidade de Tempo (Pior Caso): O(n), sendo n o tamanho da lista
   * @note Complexidade de Espaço: Θ(1)
   * @note Posição = Índice + 1
   */
  void inserir_meio(const int valor, const std::size_t posicao);

  /**
   * @brief Remove o elemento que está no inicio da lista, caso exista.
   * @note Complexidade de Tempo: Θ(1)
   * @note Complexidade de Espaço: Θ(1)
   */
  void remover_inicio();

  /**
   * @brief Remove o elemento que está no fim da lista, caso exista.
   * @note Complexidade de Tempo: O(n), sendo n o tamanho da lista.
   * @note Complexidade de Espaço: Θ(1).
   */
  void remover_fim();

  /**
   * @brief Remove o elemento que está na posição escolhida, caso exista.
   * @param posicao Posição do elemento que deseja remover.
   * @throw std::invalid_argument Se a posição for fora dos limites.
   * @note Complexidade de Tempo (Pior Caso): O(n), sendo n o tamanho da lista.
   * @note Complexidade de Espaço: Θ(1).
   * @note Posição = Índice + 1
   */
  void remover_meio(const std::size_t posicao);

  /**
   * @brief Retorna o tamanho atual da lista.
   * @return std::size_t Tamanho da lista.
   * @note Complexidade de Tempo: Θ(1);
   * @note Complexidade de Espaço: Θ(1);
   */
  std::size_t tamanho();

  /**
   * @brief Diz se a lista está vazia.
   * @return bool true caso esteja vazia; false caso contrário.
   * @note Complexidade de Tempo: Θ(1);
   * @note Complexidade de Espaço: Θ(1);
   */
  bool vazia();

  /**
   * @brief Remove todos os elementos da lista.
   * @note Complexidade de Tempo (Pior Caso): O(n);
   * @note Complexidade de Espaço: Θ(1);
   */
  void limpar();

  /**
   * @brief Inverte a ordem dos elementos da lista.
   * @note Complexidade de Tempo (Pior Caso): O(n);
   * @note Complexidade de Espaço: Θ(1);
   */
  void inverter();
};
