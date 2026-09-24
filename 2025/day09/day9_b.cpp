#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using Point = std::pair<long long, long long>;

struct Edge {
  long long aligned{};
  long long min{};
  long long max{};
};

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

  std::vector<Edge> vert_edges{}, horz_edges{};

  auto Points{parse_input("./input")};

  for (size_t i{0}; i < Points.size(); i++) {
    for (size_t j{i + 1}; j < Points.size(); j++) {
      if (Points[i].first == Points[j].first) {
        vert_edges.emplace_back(Points[i].first,
                                std::min(Points[i].second, Points[j].second),
                                std::max(Points[i].second, Points[j].second));
      }
      if (Points[i].second == Points[j].second) {
        horz_edges.emplace_back(Points[i].second,
                                std::min(Points[i].first, Points[j].first),
                                std::max(Points[i].first, Points[j].first));
      }
    }
  }

  auto area_contains_no_edges =
      [&vert_edges, &horz_edges](const Point &a, const Point &b) -> bool {
    auto x_min{std::min(a.first, b.first)};
    auto x_max{std::max(a.first, b.first)};
    auto y_min{std::min(a.second, b.second)};
    auto y_max{std::max(a.second, b.second)};

    for (const Edge &e : vert_edges) {
      if ((x_min < e.aligned && e.aligned < x_max) && e.max > y_min &&
          e.min < y_max) {
        return false;
      }
    }

    for (const Edge &e : horz_edges) {
      if (y_min < e.aligned && e.aligned < y_max && e.max > x_min &&
          e.min < x_max) {
        return false;
      }
    }

    return true;
  };

  long long max_area{0};
  for (size_t i{0}; i < Points.size(); i++) {
    for (size_t j{i + 1}; j < Points.size(); j++) {
      if (area_contains_no_edges(Points[i], Points[j])) {
        max_area = std::max(max_area, calc_area(Points[i], Points[j]));
      }
    }
  }

  std::cout << max_area << std::endl;
}
