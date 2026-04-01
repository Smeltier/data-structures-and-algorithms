#include <vector>
#include <cmath>
#include <algorithm>


std::vector<std::vector<double>> eliminacao_gaussiana(const std::vector<std::vector<double>> &, const std::vector<double> &);
std::vector<std::vector<double>> criar_matriz_aumentada(const std::vector<std::vector<double>> &, const std::vector<double> &);
int encontrar_pivo(const std::vector<std::vector<double>> &, const int, const int);
void trocar_linhas(std::vector<std::vector<double>> &, const int, const int);


std::vector<std::vector<double>> eliminacao_gaussiana(const std::vector<std::vector<double>> &A, const std::vector<double> &B) {
  std::vector<std::vector<double>> resultado = criar_matriz_aumentada(A, B);

  const int LINHAS = (int) resultado.size();
  const int COLUNAS = (int) resultado[0].size();

  for (int j = 0; j < std::min(LINHAS, COLUNAS - 1); ++j) {
    int linha_pivo = encontrar_pivo(resultado, j, j);

    if (std::abs(resultado[linha_pivo][j]) < 1e-15) {
      continue;
    }

    if (linha_pivo != j) {
      trocar_linhas(resultado, j, linha_pivo);
    }

    for (int i = j + 1; i < LINHAS; ++i) {
      const double k = resultado[i][j] / resultado[j][j];

      for (int l = j; l < COLUNAS; ++l) {
        if (l == j) {
          resultado[i][l] = 0;
        }
        else {
          resultado[i][l] -= k * resultado[j][l];
        }
      }
    }

  }

  return resultado;
}


void trocar_linhas(std::vector<std::vector<double>> &mat, const int L1, const int L2) {
  std::swap(mat[L1], mat[L2]);
}


int encontrar_pivo(const std::vector<std::vector<double>> &mat, const int coluna, const int inicio) {
  int melhor = inicio;
  double valor_maximo = std::abs(mat[inicio][coluna]);

  for (int i = inicio + 1; i < mat.size(); ++i) {
    double valor = std::abs(mat[i][coluna]);

    if (valor > valor_maximo) {
      valor_maximo = valor;
      melhor = i;
    }
  }

  return melhor;
}


std::vector<std::vector<double>> criar_matriz_aumentada(const std::vector<std::vector<double>> &A, const std::vector<double> &B) {
  const int LINHAS = (int) A.size();
  const int COLUNAS = (int) A[0].size() + 1;

  std::vector<std::vector<double>> resultado(LINHAS, std::vector<double>(COLUNAS, 0));

  for (int linha = 0; linha < LINHAS; ++linha) {
    for (int coluna = 0; coluna < A[0].size(); ++coluna) {
      resultado[linha][coluna] = A[linha][coluna];
    }

    resultado[linha][COLUNAS - 1] = B[linha];
  }

  return resultado;
}

