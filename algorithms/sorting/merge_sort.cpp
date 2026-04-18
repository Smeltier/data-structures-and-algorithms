#include <vector>

void merge(std::vector<int> &V, const int START, const int MIDDLE, const int END) {
  std::vector<int> left(V.begin() + START, V.begin() + MIDDLE + 1);
  std::vector<int> right(V.begin() + MIDDLE + 1, V.begin() + END + 1);

  int i = 0;
  int j = 0;
  int k = START;

  while (i < (int) left.size() and j < (int) right.size()) {
    if (left[i] <= right[j])
      V[k++] = left[i++];
    else
      V[k++] = right[j++];
  }

  while (i < (int) left.size())
    V[k++] = left[i++];
  while (j < (int)right.size())
    V[k++] = right[j++];
}

void merge_sort(std::vector<int> &V, const int START, const int END) {
  if (START >= END) return;

  int middle = START + (END - START) / 2;

  merge_sort(V, START, middle);
  merge_sort(V, middle + 1, END);
  merge(V, START, middle, END);
}

void merge_sort(std::vector<int> &V) {
  if (V.empty()) return;
  merge_sort(V, 0, (int) V.size() - 1);
}
