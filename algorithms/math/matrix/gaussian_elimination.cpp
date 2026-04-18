#include <vector>
#include <cmath>
#include <algorithm>

std::vector<std::vector<double>> gaussian_elimination(const std::vector<std::vector<double>> &, const std::vector<double> &);
std::vector<std::vector<double>> create_augmented_matrix(const std::vector<std::vector<double>> &, const std::vector<double> &);
int find_pivot(const std::vector<std::vector<double>> &, const int, const int);
void swap_lines(std::vector<std::vector<double>> &, const int, const int);

std::vector<std::vector<double>> gaussian_elimination(const std::vector<std::vector<double>> &A, const std::vector<double> &B) {
  std::vector<std::vector<double>> result = create_augmented_matrix(A, B);

  const int ROWS = (int) result.size();
  const int COLS = (int) result[0].size();

  for (int j = 0; j < std::min(ROWS, COLS - 1); ++j) {
    int pivot_row = find_pivot(result, j, j);

    if (std::abs(result[pivot_row][j]) < 1e-15) {
      continue;
    }

    if (pivot_row != j) {
      swap_lines(result, j, pivot_row);
    }

    for (int i = j + 1; i < ROWS; ++i) {
      const double k = result[i][j] / result[j][j];

      for (int l = j; l < COLS; ++l) {
        if (l == j) {
          result[i][l] = 0;
        }
        else {
          result[i][l] -= k * result[j][l];
        }
      }
    }

  }

  return result;
}

void swap_lines(std::vector<std::vector<double>> &mat, const int L1, const int L2) {
  std::swap(mat[L1], mat[L2]);
}

int find_pivot(const std::vector<std::vector<double>> &MAT, const int COL, const int start) {
  int best = start;
  double max_value = std::abs(MAT[start][COL]);

  for (int i = start + 1; i < MAT.size(); ++i) {
    double value = std::abs(MAT[i][COL]);

    if (value > max_value) {
      max_value = value;
      best = i;
    }
  }

  return best;
}

std::vector<std::vector<double>> create_augmented_matrix(const std::vector<std::vector<double>> &A, const std::vector<double> &B) {
  const int ROWS = (int) A.size();
  const int COLS = (int) A[0].size() + 1;

  std::vector<std::vector<double>> augmented_matrix(ROWS, std::vector<double>(COLS, 0));

  for (int row = 0; row < ROWS; ++row) {
    for (int col = 0; col < COLS - 1; ++col) {
      augmented_matrix[row][col] = A[row][col];
    }

    augmented_matrix[row][COLS - 1] = B[row];
  }

  return augmented_matrix;
}

