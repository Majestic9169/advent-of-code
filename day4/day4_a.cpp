#include <bits/stdc++.h>
#include <cstddef>
#include <fstream>
#include <vector>
using namespace std;

void update_queue(vector<vector<int>> &q, const string &row, const int &idx) {
  for (size_t i = 0; i < row.length(); i++) {
    if (row[i] == '@') {
      q[idx - 1][i]++;
      q[idx + 1][i]++;
      if (i > 0) {
        q[idx - 1][i - 1]++;
        q[idx][i - 1]++;
        q[idx + 1][i - 1]++;
      }
      if (i < row.length() - 1) {
        q[idx - 1][i + 1]++;
        q[idx][i + 1]++;
        q[idx + 1][i + 1]++;
      }
    }
  }
  // for (auto e : q[idx - 1])
  //   cout << e;
  // cout << "\n";
}

int check_row(const vector<int> &line, string &prev_row) {
  // sanity check
  if (line.size() != prev_row.length()) {
    cerr << "error: row length not equal to input length\n";
    exit(1);
  }

  int count{0};
  for (size_t i = 0; i < line.size(); i++) {
    if (prev_row[i] == '@' && line[i] < 4) {
      count++;
      prev_row[i] = '.';
    }
  }
  return count;
}

int main() {
  ifstream input{"./input", ios_base::in};

  vector<string> grid;
  string row;

  while (input >> row) {
    grid.push_back(std::move(row));
  }

  long long count{0};
  long long result{0};
  do {
    result = 0;
    int column{1};
    vector<int> v(grid[0].length(), 0);
    vector<vector<int>> q(3, v);

    update_queue(q, grid[0], column);
    // pop unnecessary top row
    q.erase(q.begin());
    q.emplace_back(vector<int>(grid[0].length(), 0));

    for (size_t i = 1; i < grid.size(); i++) {
      update_queue(q, grid[i], column);
      result += check_row(q[column - 1], grid[i - 1]);
      column++;
      q.emplace_back(vector<int>(grid[0].length(), 0));
    }

    result += check_row(q[column - 1], grid[grid.size() - 1]);
    count += result;
  } while (result != 0);

  cout << count << '\n';
}
