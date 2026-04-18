#include <utility>
#include <vector>

int lomuto_partition(std::vector<int> &, int, int);
int hoare_partition(std::vector<int> &, int, int);
void quick_sort(std::vector<int> &);
void quick_sort(std::vector<int> &, int, int);

void quick_sort(std::vector<int> &V) {
  quick_sort(V, 0, V.size() - 1);
}

void quick_sort(std::vector<int> &V, int start, int end) {
  if (start >= end) return;

  int pivot_position = lomuto_partition(V, start, end);
  quick_sort(V, start, pivot_position - 1);
  quick_sort(V, pivot_position + 1, end);
}

// Lomuto's Pivot
int lomuto_partition(std::vector<int> &V, int start, int end) {
  int pivot_position = start;
  int right = start + 1;
  int left = start + 1;

  for (int i = right; i < V.size(); ++i) {
    if (V[i] <= V[pivot_position]) {
      std::swap(V[left], V[i]);
      left++;
    }
  }

  left--;
  std::swap(V[pivot_position], V[left]);
  return left;
}

// Hoare's Pivot
int hoare_partition(std::vector<int> &V, int start, int end) {
  int pivot = V[start + (end - start) / 2];
  int i = start - 1;
  int j = end + 1;

  while (true) {
    do {
      i++;
    } while (V[i] < pivot);

    do {
      j--;
    } while (V[j] > pivot);

    if (i >= j) return j;

    std::swap(V[i], V[j]);
  }
}
