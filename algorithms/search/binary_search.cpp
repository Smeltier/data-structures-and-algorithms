#include <vector>

int binary_search(const std::vector<int> &V, const int VALUE) {
  int left = 0;
  int right = (int) V.size() - 1;

  while (left <= right) {
    int middle = left + (right - left) / 2;

    if (VALUE == V[middle]) {
      return middle + 1;
    }
    else if (VALUE < V[middle]) {
      right = middle - 1;
    }
    else {
      left = middle + 1;
    }
  }

  return 0;
}
