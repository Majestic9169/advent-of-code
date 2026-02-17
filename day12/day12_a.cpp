#include <array>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <utility>
using namespace std;

typedef array<array<bool, 3>, 3> shape_t;
typedef pair<pair<int, int>, vector<int>> region_t;

// print shape
void print_shape(const shape_t &shape) {
  for (auto &&s : shape) {
    for (auto &&e : s) {
      cout << e;
    }
    cout << endl;
  }
  cout << endl;
}

// print region
void print_region(const region_t &region) {
  cout << region.first.first << " x " << region.first.second << endl;
  for (const auto &e : region.second) {
    cout << e << ", ";
  }
  cout << endl << endl;
}

// shape area
int shape_area(const shape_t &shape) {
  int area{0};
  for (auto &&s : shape) {
    for (auto &&e : s) {
      area += e == true ? 1 : 0;
    }
  }
  return area;
}

int main() {
  vector<shape_t> shapes{};
  vector<region_t> regions{};

  ifstream infile{"./input"};
  string line{};

  while (infile >> line) {
    if (line.find('x') == string::npos) {
      char c;
      shape_t shape{};
      for (auto &&s : shape) {
        for (auto &&e : s) {
          infile >> c;
          e = c == '#' ? true : false;
        }
      }
      shapes.emplace_back(std::move(shape));
      // print_shape(shapes.back());
    } else {
      int x = atoi(string(line.begin(), line.begin() + line.find('x')).c_str());
      int y =
          atoi(string(line.begin() + line.find('x') + 1, line.end()).c_str());
      regions.push_back(make_pair(make_pair(x, y), vector<int>(shapes.size())));
      for (auto &&e : regions.back().second) {
        infile >> e;
      }
      // print_region(regions.back());
    }
  }

  long long answer{0};
  for (const region_t &region : regions) {
    long long area = region.first.first * region.first.second;
    long long required_area{0};
    for (size_t i = 0; i < region.second.size(); i++) {
      if (region.second[i]) {
        required_area += region.second[i] * shape_area(shapes[i]);
      }
    }
    if (required_area <= area) {
      answer++;
    }
  }

  /*
   * THAT WORKED WHAT THE FUCK
   * I CAN'T BELIEVE THAT WAS ENOUGH OMG
   */
  cout << answer << endl;
}
