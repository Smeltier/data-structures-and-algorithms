#include <utility>
#include <vector>

void heapify(std::vector<int> &V, const int N, const int index) {
  int biggest = index;
  int left = 2 * biggest + 1;
  int right = 2 * biggest + 2;

  if (left < N and V[left] > V[biggest]) {
    biggest = left;
  }

  if (right < N and V[right] > V[biggest]) {
    biggest = right;
  }

  if (biggest != index) {
    std::swap(V[index], V[biggest]);
    heapify(V, N, biggest);
  }
}

void heap_sort(std::vector<int> &V) {
  const int N = (int) V.size();

  for (int i = N / 2 - 1; i >= 0; --i) {
    heapify(V, N, i);
  }

  for (int i = N - 1; i > 0; --i) {
    std::swap(V[0], V[i]);
    heapify(V, i, 0);
  }
}
