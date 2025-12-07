#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  ifstream input{"./input", ios_base::in};

  int count{50};
  int password{0};
  char dir;
  int distance;
  int old_count;
  while (input >> dir >> distance) {
    int q = distance / 100;
    int r = distance % 100;
    old_count = count;
    password += q;
    if (dir == 'L') {
      count = count - r;
      if (count <= 0 && old_count) {
        password++;
      }
    } else if (dir == 'R') {
      count = count + r;
      if (count >= 100 && old_count) {
        password++;
      }
    }
    count = (count + 100) % 100;
    // printf("%3d [%c%d] %2d to %2d\n", password, dir, distance, old_count,
    // count);
  }
  cout << "FINAL PASSWORD: " << password << endl;
}
