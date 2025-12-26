#include <bits/stdc++.h>
#include <cstddef>
using namespace std;

unsigned long long quantum_traverse(const vector<string> &manifold,
                                    const size_t &beam_position,
                                    const int &curr_line = 0) {

  static unsigned long long timelines{1};

  if (static_cast<size_t>(curr_line) >= manifold.size() &&
      beam_position < manifold[curr_line].size()) {
    return timelines;
  }

  switch (manifold[curr_line][beam_position]) {
  case '^':
    quantum_traverse(manifold, beam_position - 1, curr_line + 1);
    timelines++;
    quantum_traverse(manifold, beam_position + 1, curr_line + 1);
    break;
  case '.':
    quantum_traverse(manifold, beam_position, curr_line + 1);
    break;
  }

  return timelines;
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
      timelines = quantum_traverse(manifold, i, 1);
      break;
    }
  }

  cout << timelines << "\n";
}
