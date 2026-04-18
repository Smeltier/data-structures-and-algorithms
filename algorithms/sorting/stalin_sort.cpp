#include <vector>

void stalin_sort(std::vector<int> &V) {
  if (V.empty()) return;

  std::vector<int> result;
  result.push_back(V[0]);

  for (int it = 1; it < (int) V.size(); ++it) {
    if (V[it] >= result.back()) {
      result.push_back(V[it]);
    }
  }

  V = std::move(result);
}
