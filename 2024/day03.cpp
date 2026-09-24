#include "util.hpp"
#include <string>
#include <string_view>

namespace day03 {

auto parta(std::string_view input) -> long long {
  long long result{0};
  for (size_t i{0}; i < input.size(); i++) {
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
