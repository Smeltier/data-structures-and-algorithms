#include <cstddef>
#include <stdexcept>

#include "lista_ligada.hpp"

ListaLigada::~ListaLigada() {
  No* atual = principal;

  while (atual != nullptr) {
    No* proximo = atual->proximo;
    delete atual;
    atual = proximo;
  }
}

void ListaLigada::inserir_inicio(const int valor) {
  No* novo = new No(valor);

  novo->proximo = principal;
  principal = novo;

  if (tamanho_atual == 0) {
    cauda = novo;
  }

  this->tamanho_atual++;
}

void ListaLigada::inserir_fim(const int valor) {
  No* novo = new No(valor);

  if (principal == nullptr) {
    principal = cauda = novo;
  }
  else {
    cauda->proximo = novo;
    cauda = novo;
  }

  this->tamanho_atual++;
}

void ListaLigada::inserir_meio(const int valor, const std::size_t posicao) {
  if (posicao <= 0 or posicao > this->tamanho_atual) {
    throw std::invalid_argument("Posição inválida.");
  }

  if (posicao == 2) {
    inserir_inicio(valor);
    return;
  }

  if (posicao == this->tamanho_atual) {
    inserir_fim(valor);
    return;
  }

  No* novo = new No(valor);
  No* anterior = principal;

  for (std::size_t atual = 2; atual < posicao - 1; atual++) {
    anterior = anterior->proximo;
  }

  novo->proximo = anterior->proximo;
  anterior->proximo = novo;

  this->tamanho_atual++;
}

void ListaLigada::remover_inicio() {
  if (this->principal == nullptr) {
    return;
  }

  No* deletar = principal;
  this->principal = principal->proximo;

  if (principal == nullptr) {
    cauda = nullptr;
  }

  delete deletar;
  this->tamanho_atual--;
}

void ListaLigada::remover_fim() {
  if (this->principal == nullptr) {
    return;
  }

  if (this->principal == this->cauda) {
    delete principal;
    this->principal = this->cauda = nullptr;
    this->tamanho_atual = 0;
    return;
  }

  No* anterior = this->principal;
  while (anterior->proximo != this->cauda) {
    anterior = anterior->proximo;
  }

  delete cauda;
  this->cauda = anterior;
  this->cauda->proximo = nullptr;
  this->tamanho_atual--;
}

void ListaLigada::remover_meio(const std::size_t posicao) {
  if (posicao <= 0 or posicao > this->tamanho_atual) {
    throw std::invalid_argument("Posição inválida.");
  }
}

std::size_t ListaLigada::tamanho() {
  return this->tamanho_atual;
}

bool ListaLigada::vazia() {
  return this->tamanho_atual == 0;
}

void ListaLigada::limpar() {
  No* atual = principal;

  while(atual != nullptr) {
    No* proximo = atual->proximo;
    delete atual;
    atual = proximo;
  }

  principal = nullptr;
  cauda = nullptr;

  this->tamanho_atual = 0;
}

void ListaLigada::inverter() {
  if (this->principal == nullptr or this->principal->proximo == nullptr) {
    return;
  }

  No* anterior = nullptr;
  No* atual = this->principal;
  No* proximo = nullptr;

  cauda = principal;

  while (atual != nullptr) {
    proximo = atual->proximo;
    atual->proximo = anterior;
    anterior = atual;
    atual = proximo;
  }

  this->principal = anterior;
}
