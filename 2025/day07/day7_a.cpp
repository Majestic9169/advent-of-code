#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream infile{"./input", ios_base::in};
  vector<string> manifold{};
  string line{};
  while (infile >> line) {
    manifold.emplace_back(std::move(line));
  }

  vector<bool> active_beams(manifold[0].size(), false);
  unsigned long long split_count{0};

  for (size_t i = 0; i < manifold.size(); i++) {
    for (size_t j = 0; j < active_beams.size(); j++) {
      switch (manifold[i][j]) {
      case 'S':
        active_beams[j] = true;
        break;
      case '^':
        if (active_beams[j]) {
          split_count++;
          active_beams[j] = false;
          if (j != 0) {
            active_beams[j - 1] = true;
          }
          if (j != active_beams.size() - 1) {
            active_beams[j + 1] = true;
          }
        }
        break;
      }
    }
  }

  cout << split_count << "\n";
}
