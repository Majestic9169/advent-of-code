#include "util.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace day02 {

auto parse_input(std::string input) -> std::vector<std::vector<int>> {
  std::vector<std::vector<int>> result;
  std::istringstream iss{input};
  std::string line{};
  while (std::getline(iss, line)) {
    std::istringstream iss2{line};
    std::vector<int> a;
    int x;
    while (iss2 >> x)
      a.push_back(x);
    result.emplace_back(std::move(a));
  }
  return result;
}

auto parta(std::string_view input) -> long long {
  auto reports = parse_input(std::string{input});
  long long safe{0};
  for (const auto &report : reports) {
    bool increasing{report.front() < report.back()};
    bool is_safe{true};
    for (size_t i{1}; i < report.size(); i++) {
      auto diff = report[i] - report[i - 1];
      diff = increasing ? diff : -diff;

      if (diff < 1 || diff > 3) {
        is_safe = false;
      }
    }
    safe += is_safe;
  }
  return safe;
}

auto partb(std::string_view input) -> long long {
  auto reports = parse_input(std::string{input});
  long long safe{0};
  for (const auto &raw_report : reports) {
    for (int removed{-1}; removed < static_cast<int>(raw_report.size());
         removed++) {
      bool is_safe{true};
      auto report{raw_report};
      if (removed != -1) {
        report.erase(report.begin() + removed);
      }
      bool increasing{report.front() < report.back()};

      for (size_t i{1}; i < report.size(); i++) {
        auto diff = report[i] - report[i - 1];
        diff = increasing ? diff : -diff;

        if (diff < 1 || diff > 3) {
          is_safe = false;
        }
      }

      if (is_safe) {
        safe++;
        break;
      }
    }
  }
  return safe;
}

REGISTER_DAY(2, parta, partb);

} // namespace day02
