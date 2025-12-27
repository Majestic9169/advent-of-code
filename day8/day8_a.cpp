#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <chrono>
#include <cmath>
#include <functional>
#include <ios>
#include <iterator>
#include <queue>
#include <random>
#include <unordered_map>
#include <utility>
using namespace std;

using ll = long long;

vector<int> split(string &s, const string &delim) {
  vector<int> tokens{};
  size_t pos{0};

  while ((pos = s.find(delim)) != std::string::npos) {
    tokens.emplace_back(atoi(s.substr(0, pos).c_str()));
    s.erase(0, pos + delim.length());
  }
  tokens.emplace_back(atoi(s.c_str()));

  return tokens;
}

struct Point {
  ll x;
  ll y;
  ll z;

  Point(const ll &x_, const ll &y_, const ll &z_) : x{x_}, y{y_}, z{z_} {};

  double distance_from(const Point &pt) const {
    unsigned long long dist{0};
    dist += (pt.x - x) * (pt.x - x);
    dist += (pt.y - y) * (pt.y - y);
    dist += (pt.z - z) * (pt.z - z);
    return sqrt(dist);
  }
};

bool operator==(const Point &a, const Point &b) {
  return a.x == b.x and a.y == b.y and a.z == b.z;
}

struct Pair {
  int pt1;
  int pt2;
  double distance;

  void swap() {
    int tmp = pt1;
    pt1 = pt2;
    pt2 = tmp;
  }
};

struct PairCmp {
  bool operator()(const Pair &a, const Pair &b) {
    return a.distance > b.distance;
  }
};

class ClosestPoints {
private:
  double min_dist{MAXFLOAT};
  vector<Point> pts{};
  pair<int, int> best_pair;

  struct CustomHashPoint {
    size_t operator()(const Point &p) const {
      static const unsigned long long int C =
          std::chrono::steady_clock::now().time_since_epoch().count();
      unsigned long long h{hash<ll>{}(p.x)};
      h ^= hash<ll>{}(p.y);
      h ^= hash<ll>{}(p.z);
      return C ^ h;
    }
  };

public:
  priority_queue<Pair, vector<Pair>, PairCmp> pq{};

  ClosestPoints(const vector<Point> &boxes) : pts{boxes}, best_pair({0, 0}) {
    closest();
  };

  void closest() {
    int n = static_cast<int>(pts.size());
    assert(n >= 2);

    unordered_map<Point, int, CustomHashPoint> previous{};
    for (int i = 0; i < static_cast<int>(pts.size()); i++) {
      auto it = previous.find(pts[i]);
      if (it != previous.end()) {
        best_pair = {it->second, i};
      }
      previous[pts[i]] = i;
    }

    unordered_map<Point, vector<int>, CustomHashPoint> grid;
    grid.reserve(n);

    mt19937 rd(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dis(0, n - 1);

    double d2 = pts[0].distance_from(pts[1]);
    pair<int, int> closest = {0, 1};

    auto candidate_closest = [&](int i, int j) -> void {
      double ab2 = pts[i].distance_from(pts[j]);
      // NOTE: couldn't figure out how to handle duplicates
      pq.push({i, j, ab2});
      if (ab2 < d2) {
        d2 = ab2;
        closest = {i, j};
      }
    };

    for (int i = 0; i < n; i++) {
      int j = dis(rd);
      int k = dis(rd);
      while (j == k) {
        k = dis(rd);
      }
      candidate_closest(j, k);
    }

    long long d = static_cast<long long>(d2 + 1);

    for (int i = 0; i < n; i++) {
      grid[Point(pts[i].x / d, pts[i].y / d, pts[i].z / d)].push_back(i);
    }

    for (const auto &it : grid) {
      int k = int(it.second.size());
      for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
          candidate_closest(it.second[i], it.second[j]);
        }
      }
    }

    for (const auto &it : grid) {
      auto coord = it.first;
      for (int dx = 0; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          for (int dz = -1; dz <= 1; dz++) {
            if (dx == 0 && dy == 0 && dz == 0)
              continue;
            Point neighbour(coord.x + dx, coord.y + dy, coord.z + dz);

            for (int i : it.second) {
              if (!grid.count(neighbour))
                continue;
              for (int j : grid.at(neighbour)) {
                candidate_closest(i, j);
              }
            }
          }
        }
      }
    }

    best_pair = closest;
  }
};

class UnionFind {
private:
  vector<int> parent;
  vector<int> size;

public:
  UnionFind(const size_t &sz) : parent(sz), size(sz, 1) {
    for (size_t i = 0; i < sz; i++)
      parent[i] = static_cast<int>(i);
  }

  int find_set(int v) {
    if (v == parent[v])
      return v;
    return parent[v] = find_set(parent[v]);
  }

  void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (size[a] < size[b]) {
        swap(a, b);
      }
      parent[b] = a;
      size[a] += size[b];
    }
  }

  int ans() const {
    vector<int> tmp(size.begin(), size.end());
    sort(tmp.begin(), tmp.end(), std::greater<int>());
    return tmp[0] * tmp[1] * tmp[2];
  }
};

int main() {
  ifstream infile{"./input", ios_base::in};
  vector<Point> boxes{};
  vector<int> c(3);
  string line{};

  while (infile >> line) {
    c = split(line, ",");
    boxes.emplace_back(Point(c[0], c[1], c[2]));
  }

  ClosestPoints cp(boxes);
  UnionFind uf(boxes.size());

  pair<int, int> prev = {-1, -1};
  for (int i = 0; i < 1000 && !cp.pq.empty(); i++) {
    Pair p = cp.pq.top();
    cp.pq.pop();

    if (p.pt1 > p.pt2) {
      swap(p.pt1, p.pt2);
    }

    // NOTE: handle duplicates
    pair<int, int> curr = {p.pt1, p.pt2};
    if (curr == prev) {
      i--;
      continue;
    }

    uf.union_sets(p.pt1, p.pt2);

    prev = curr;
  }

  cout << uf.ans() << endl;
}
