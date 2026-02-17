#include <bits/stdc++.h>
#include <deque>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

/* print graph */
void print_graph(const unordered_map<string, vector<string>> &graph) {
  cout << endl;
  for (const auto &n : graph) {
    cout << n.first << ": ";
    for (const auto &e : n.second) {
      cout << e << " ";
    }
    cout << endl;
  }
}

int main() {
  unordered_map<string, vector<string>> graph{};
  unordered_map<string, bool> visited{};
  string line{};
  ifstream infile{"./input"};

  /* parse graph */
  while (getline(infile, line)) {
    istringstream iss{line};
    string node;
    string node_buf;
    vector<string> adj_list{};
    iss >> node;
    node.pop_back();
    while (iss >> node_buf) {
      adj_list.emplace_back(std::move(node_buf));
    }

    graph[node] = adj_list;
    visited[node] = false;
  }

  // print_graph(graph);

  /* dfs on graph */
  long long num_paths{0};
  deque<string> dfs_q{};
  dfs_q.push_back("you");

  while (!dfs_q.empty()) {
    string node{dfs_q.front()};
    dfs_q.pop_front();

    if (node == "out") {
      num_paths++;
      // cout << "[+] Reached 'out' | " << num_paths << endl;
      continue;
    }

    visited[node] = true;
    for (const string &n : graph[node]) {
      if (!visited[n]) {
        dfs_q.push_back(n);
      }
    }
  }

  cout << num_paths << endl;
}
