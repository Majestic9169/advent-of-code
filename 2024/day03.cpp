#include "util.hpp"
#include <iostream>
#include <ranges>
#include <regex>
#include <string>
#include <string_view>

namespace day03 {

auto matches(std::string_view str, const std::regex &re) {
  return std::ranges::subrange(
      std::cregex_iterator(str.data(), str.data() + str.size(), re),
      std::cregex_iterator());
}

auto parta(std::string_view input) -> long long {
  std::regex r{R"(mul\((\d+),(\d+)\))"};

  long long result{0};
  for (const auto &match : matches(input, r)) {
    result += std::stoll(match[1].str()) * std::stoll(match[2].str());
  }

  return result;
}

auto partb(std::string_view input) -> long long {
  long long result{0};
  bool enabled{true};
  for (size_t i{0}; i < input.size(); i++) {
    if (input.substr(i, 7) == "don't()") {
      enabled = false;
      i += 6;
      continue;
    } else if (input.substr(i, 4) == "do()") {
      enabled = true;
      i += 3;
      continue;
    }

    if (enabled) {
      long long a{0}, b{0};
      std::string stra{}, strb{};
      if (input.substr(i, 4) == "mul(") {
        i += 4;

        while (input[i] != ',' && input[i] >= '0' && input[i] <= '9') {
          stra += input[i++];
        }
        if (input[i] != ',')
          continue;
        i++;
        while (input[i] != ')' && input[i] >= '0' && input[i] <= '9') {
          strb += input[i++];
        }
        if (input[i] != ')')
          continue;

        a = std::stoll(stra);
        b = std::stoll(strb);
        result += a * b;
      }
    }
  }

  return result;
}

REGISTER_DAY(3, parta, partb);
} // namespace day03
