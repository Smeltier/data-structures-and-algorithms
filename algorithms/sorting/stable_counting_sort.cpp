#include <algorithm>
#include <vector>

void stable_counting_sort(std::vector<int> &V) {
  if (V.empty()) return;

  auto [min_it, max_it] = std::minmax_element(V.begin(), V.end());
  const int min_element = *min_it;
  const int max_element = *max_it;

  std::vector<int> count(max_element - min_element + 1, 0);

  for (int it = 0; it < (int) V.size(); ++it) {
    count[V[it] - min_element]++;
  }

  for (int it = 1; it < (int) count.size(); ++it) {
    count[it] += count[it - 1];
  }

  std::vector<int> copy(V.begin(), V.end());

  for (int it = (int) V.size() - 1; it >= 0; --it) {
    int position = count[copy[it] - min_element] - 1;
    V[position] = copy[it];
    count[copy[it] - min_element]--;
  }
}
