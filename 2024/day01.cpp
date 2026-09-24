#include "util.hpp"
#include <algorithm>
#include <cstddef>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace day01 {

auto parse_input(std::string input)
    -> std::pair<std::vector<int>, std::vector<int>> {
  std::vector<int> list_a{}, list_b{};
  std::istringstream iss{input};
  int a, b;
  while (iss >> a >> b) {
    list_a.emplace_back(a);
    list_b.emplace_back(b);
  }
  return std::make_pair(list_a, list_b);
}

auto parta(std::string_view input) -> long long {
  auto [lista, listb] = parse_input(std::string(input));
  std::ranges::sort(lista);
  std::ranges::sort(listb);
  long long sum{0};
  for (size_t i{0}; i < lista.size(); i++) {
    sum += abs(lista[i] - listb[i]);
  }
  return sum;
}

auto partb(std::string_view input) -> long long {
  auto [lista, listb] = parse_input(std::string(input));
  std::unordered_map<int, int> fb;
  for (size_t i{0}; i < lista.size(); i++) {
    fb[listb[i]]++;
  }
  long long score{0};
  for (size_t i{0}; i < lista.size(); i++) {
    score += lista[i] * fb[lista[i]];
  }
  return score;
}

REGISTER_DAY(1, parta, partb);

} // namespace day01
