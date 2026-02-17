#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <ios>
#include <sstream>
#include <string>
using namespace std;

enum OPERATION { ADD, MUL };

int main() {
  ifstream infile{"./input", ios_base::in};
  vector<string> input{};
  vector<OPERATION> op{};
  string line{};

  while (getline(infile, line)) {
    input.emplace_back(std::move(line));
  }

  for (char c : input.back()) {
    switch (c) {
    case '+':
      op.push_back(ADD);
      break;
    case '*':
      op.push_back(MUL);
      break;
    default:
      break;
    }
  }

  vector<unsigned long long int> ans(op.size());
  for (size_t i = 0; i < ans.size(); i++)
    ans[i] = static_cast<int>(op[i]);

  for (auto itr = input.begin(); itr != input.end() - 1; itr++) {
    line = *itr;
    int x;
    istringstream iss{line};
    int count = 0;
    while (iss >> x) {
      if (op[count] == ADD) {
        ans[count++] += x;
      } else if (op[count] == MUL) {
        ans[count++] *= x;
      }
    }
  }

  unsigned long long int solve{0};
  for (const auto &e : ans)
    solve += e;

  cout << solve << "\n";
}
