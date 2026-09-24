#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using Point = std::pair<long long, long long>;

std::vector<Point> parse_input(std::filesystem::path infile) {
  std::vector<Point> result{};
  std::ifstream ifile{infile};
  long long pointa, pointb;
  char comma;
  while (ifile >> pointa >> comma >> pointb) {
    result.emplace_back(pointa, pointb);
  }
  return result;
}

int main() {
  auto calc_area = [](const Point &pta, const Point &ptb) -> long long {
    return (abs(static_cast<int>(pta.first - ptb.first)) + 1LL) *
           (abs(static_cast<int>(pta.second - ptb.second)) + 1LL);
  };

  auto Points{parse_input("./input")};

  long long max_area{0};
  for (size_t i{0}; i < Points.size(); i++) {
    for (size_t j{i + 1}; j < Points.size(); j++) {
      max_area = std::max(max_area, calc_area(Points[i], Points[j]));
    }
  }

  std::cout << max_area << std::endl;
}
