#include <bits/stdc++.h>
#include <fstream>
#include <ios>
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
  for (size_t i = 0; i < ans.size(); i++) {
    ans[i] = static_cast<int>(op[i]);
  }

  int count{0};
  for (size_t i = 0; i < input[0].size(); i++) {
    string number{""};
    for (size_t j = 0; j < input.size() - 1; j++) {
      if (input[j][i] >= '0' && input[j][i] <= '9') {
        number += input[j][i];
      }
    }
    if (number.length()) {
      switch (op[count]) {
      case ADD:
        ans[count] += atoi(number.c_str());
        break;
      case MUL:
        ans[count] *= atoi(number.c_str());
        break;
      }
    } else {
      count++;
    }
  }

  unsigned long long int solve{0};
  for (const auto &e : ans)
    solve += e;

  cout << solve << "\n";
}
