#include <bits/stdc++.h>
#include <cstddef>
using namespace std;

unsigned long long quantum_traverse(const vector<string> &manifold,
                                    const size_t &start) {
  vector<unsigned long long> dp(manifold[0].size(), 0);
  dp[start] = 1;
  for (size_t i = 1; i < manifold.size(); i++) {
    for (size_t j = 0; j < dp.size(); j++) {
      if (manifold[i][j] == '^') {
        dp[j - 1] += dp[j];
        dp[j + 1] += dp[j];
        dp[j] = 0;
      }
    }
  }

  unsigned long long sum{0};
  for (const auto &e : dp) {
    sum += e;
  }
  return sum;
}

int main() {
  ifstream infile{"./input", ios_base::in};
  vector<string> manifold{};
  string line{};
  while (infile >> line) {
    manifold.emplace_back(std::move(line));
  }

  unsigned long long timelines{};
  for (size_t i = 0; i < manifold[0].size(); i++) {
    if (manifold[0][i] == 'S') {
      timelines = quantum_traverse(manifold, i);
      break;
    }
  }

  cout << timelines << "\n";
}
