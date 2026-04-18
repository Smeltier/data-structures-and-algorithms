#include <algorithm>
#include <vector>

void counting_sort(std::vector<int> &v) {
  if (v.empty()) return;

  auto [min_it, max_it] = std::minmax_element(v.begin(), v.end());
  const int min_element = *min_it;
  const int max_element = *max_it;

  std::vector<int> count(max_element - min_element + 1, 0);

  for (int it = 0; it < (int) v.size(); ++it) {
    count[v[it] - min_element]++;
  }

  int index = 0;
  for (int it = 0; it < (int) count.size(); ++it) {
    while (count[it] > 0) {
      v[index++] = it + min_element;
      count[it]--;
    }
  }
}
