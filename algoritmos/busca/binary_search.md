# Binary Search (Busca Binária)

### Ideia:

Algoritmo otimizado que busca se determinado elemento está presente em uma lista **ordenada**.

A busca é feita dividindo repetidamente a lista ao meio (dividir e conquistar), comparando o elemento do meio com o valor buscado.

### Algoritmo:

Dado uma lista $A$ com os valores $A_0,A_1,A_2,...,A_{n-1}$ ordenada de tal modo que $A_0 \leq A_1 \leq A_2 \leq ... \leq A_{n-1}$, e um valor para pesquisa $T$, a seguinte função usa Busca Binária para achar a posição de $T$ em $A$.

1. Defina $L$ para $0$ e $R$ para $n - 1$.
2. Enquanto $L \leq R$, faça:
   
    a. Defina $m$ para $L + \lfloor(R - L) / 2\rfloor$, ou seja, o meio do intervalo de busca.
   
    b. Se $A_m < T$, defina $L$ para $m + 1$ e recomece o laço de repetição.
   
    c. Se $A_m > T$, defina $R$ para $m - 1$ e recomece o laço de repetição.
   
    e. Se $A_m = T$, a pesquisa está feita, e a posição de $T$ é $m + 1$.

### Pseudocódigo:

```C++
BINARY_SEARCH(V, valor)
  V: Vetor ordenado.
  valor: Elemento que estamos procurando.

    esquerda <- 0
    direita <- tamanho(V) - 1

    enquanto esquerda <= direita faça
        meio <- esquerda + ⌊(direita - esquerda) / 2⌋

        se V[meio] = valor então
            retorne meio + 1    // Posição 1-based.
        senão se V[meio] > valor então
            direita <- meio - 1
        senão
            esquerda <- meio + 1

    retorne 0   // Não encontrado.
```

### Implementação:

O código implementado em C++ pode ser acessado clicando aqui: [BINARY SEARCH](binary_search.cpp)

### Complexidade de Tempo:

- Melhor caso: $O(1)$ - Elemento encontrado na primeira comparação.
- Pior caso: $O(log_2 n)$

### Complexidade de Espaço:

- O(1) - Usa apenas variáveis auxiliares.
