#pragma once

#include <format>
#include <functional>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

struct DayResult {
  int day;
  int part;
  std::string answer;
  double time_ms;
};

template <typename Func> auto wrap_part(Func func) {
  return [func](std::string_view input) -> std::string {
    auto result = func(input);
    using ReturnType =
        std::decay_t<decltype(result)>; // [removes const, ref, and volatile
                                        // qualifiers]

    if constexpr (std::is_same_v<ReturnType, std::string>) {
      return result;
    } else if constexpr (std::is_same_v<ReturnType, std::string_view>) {
      return std::string(result);
    } else {
      return std::format("{}", result);
    }
  };
}

struct Solution {
  int day;
  std::function<std::string(std::string_view)> part1;
  std::function<std::string(std::string_view)> part2;
};

class SolutionRegistry {
public:
  static SolutionRegistry &instance() {
    static SolutionRegistry reg;
    return reg;
  }

  template <typename P1, typename P2> void register_day(int day, P1 p1, P2 p2) {
    solutions_.push_back(
        Solution{.day = day, .part1 = wrap_part(p1), .part2 = wrap_part(p2)});
  }

  [[nodiscard]] const std::vector<Solution> &solutions() const noexcept {
    return solutions_;
  }

private:
  std::vector<Solution> solutions_{};
};

#define REGISTER_DAY(day, p1, p2)                                              \
  static inline const bool registered_day_##day = []() {                       \
    SolutionRegistry::instance().register_day(day, p1, p2);                    \
    return true;                                                               \
  }()
