# Eliminação Gaussiana (Escalonamento)

Implementação do algoritmo de Gauss para resolver sistemas lineares Ax = B, utilizando pivotagem parcial para melhorar a estabilidade numérica.

### Passo a Passo do Algoritmo:

1. Criar Matriz Aumentada $[A | B]$:

    Começamos combianndo a matriz de coeficientes $A$ com o vetor de termos independentes $B$.

    $$
    \left[
        \begin{array}{ccccc|c}
            a_{11} && a_{12} && a_{13} && b_{1} \\
            a_{21} && a_{22} && a_{23} && b_{2} \\
            a_{31} && a_{32} && a_{33} && b_{3}
        \end{array}
    \right]
    $$

$\newline$
$\newline$

2. Para cada coluna $j$ (eliminação):

    $\newline$
    $\newline$

    1. Encontrar o pivô (usando pivotagem parcial):

        Busca a linha com maior valor absoluto na coluna $j$, a partir da linha $j$:

        $$
        Pivô = \max_{i \geq j} | a_{ij} |
        $$


    $\newline$
    $\newline$

    2. Trocar linhas (se necessário):

        Se o $pivô$ não está na posição $j$, realiza a troca.

    $\newline$
    $\newline$

    3. Eliminar a baixo do $pivô$:

        Para cada linha $i$ abaixo do $pivô$, calcular o multiplicador:

        $$
        k_i = \frac{a_{ij}}{a_{jj}}
        $$

        E fazer a operação:

        $$
        L_i \leftarrow L_i - k_i \cdot L_j
        $$

$\newline$
$\newline$

3. Repetir para as próximas colunas:

    O processo continua para a próxima coluna até formar uma matrix triangular superior:

    $$
    \left[
        \begin{array}{ccccc|c}
            a'_{11} && a'_{12} && a'_{13} && b'_{1} \\
            0 && a'_{22} && a'_{23} && b'_{2} \\
            0 && 0 && a'_{33} && b'_{3}
        \end{array}
    \right]
    $$

### Pseudocódigo:

```
1.  ELIMINAÇÃO_GAUSSIANA(A, B)
2.    A: matriz dos coeficientes.
3.    B: vetor dos termos independentes.
4.      matriz_aumentada <- [A | B]
5.      LINHAS <- tamanho(matriz_aumentada)
6.      COLUNAS <- tamanho(matriz_aumentada[0])
7.
8.      para j <- 0 até LINHAS - 1 faça
9.          linha_pivô <-


```
