#include "util.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>
#include <string_view>
#include <vector>

namespace day04 {
auto parta(std::string_view input) -> long long {
  std::vector<std::string_view> lines{};
  auto prev{0u};
  for (auto i{0u}; i < input.size(); i++) {
    if (input[i] == '\n') {
      lines.push_back(input.substr(prev, (i - prev)));
      prev = i + 1;
    }
  }

  auto inside_grid = [&lines](int i, int j) -> bool {
    return i >= 0 && i < static_cast<int>(lines.size()) && j >= 0 &&
           j < static_cast<int>(lines[i].size());
  };

  const std::vector<int> dx{1, 1, 1, 0, 0, -1, -1, -1};
  const std::vector<int> dy{1, 0, -1, 1, -1, 1, 0, -1};

  const std::string XMAS{"XMAS"};

  auto is_xmas = [&lines, &dx, &dy, &XMAS,
                  &inside_grid](int i, int j, size_t direction) -> bool {
    for (int k{0}; k < static_cast<int>(XMAS.size()); k++) {
      int x{i + k * dx[direction]};
      int y{j + k * dy[direction]};

      if (inside_grid(x, y) && lines[x][y] == XMAS[k]) {
        continue;
      } else {
        return false;
      }
    }

    return true;
  };

  long long occurrences{0};

  for (auto i{0u}; i < lines.size(); i++) {
    for (auto j{0u}; j < lines[i].size(); j++) {
      for (auto k{0u}; k < dx.size(); k++) {
        occurrences += is_xmas(i, j, k);
      }
    }
  }

  return occurrences;
}
auto partb(std::string_view input) -> long long {
  std::vector<std::string_view> lines{};
  auto prev{0u};
  for (auto i{0u}; i < input.size(); i++) {
    if (input[i] == '\n') {
      lines.push_back(input.substr(prev, (i - prev)));
      prev = i + 1;
    }
  }

  auto inside_grid = [&lines](int i, int j) -> bool {
    return i >= 0 && i < static_cast<int>(lines.size()) && j >= 0 &&
           j < static_cast<int>(lines[i].size());
  };

  std::vector<int> dx{1, -1};
  std::vector<int> dy{1, -1};

  auto is_mas_mas = [&lines, &dx, &dy, &inside_grid](int i, int j) -> bool {
    if (lines[i][j] == 'A') {
      uint8_t count_m{0};
      uint8_t count_s{0};
      for (auto dxx : dx) {
        for (auto dyy : dy) {
          auto x{i + dxx};
          auto y{j + dyy};
          if (inside_grid(x, y)) {
            if (lines[x][y] == 'S')
              count_s++;
            if (lines[x][y] == 'M')
              count_m++;
          }
        }
      }
      if (count_s == 2 && count_m == 2 &&
          lines[i + 1][j + 1] != lines[i - 1][j - 1])
        return true;
    }
    return false;
  };

  long long occurrences{0};

  for (auto i{0u}; i < lines.size(); i++) {
    for (auto j{0u}; j < lines[i].size(); j++) {
      occurrences += is_mas_mas(i, j);
    }
  }

  return occurrences;
}
REGISTER_DAY(4, parta, partb);
} // namespace day04
