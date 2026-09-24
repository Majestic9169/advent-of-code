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
  while (input >> dir >> distance) {
    distance = distance % 100;
    if (dir == 'L') {
      count = (count - distance + 100) % 100;
    } else if (dir == 'R') {
      count = (count + distance + 100) % 100;
    }
    if (count == 0)
      password++;
  }
  cout << "FINAL PASSWORD: " << password << endl;
}
