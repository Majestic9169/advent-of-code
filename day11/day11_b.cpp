#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

typedef tuple<string, bool, bool> node_t;

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

// num paths
long long count_paths(node_t state,
                      const unordered_map<string, vector<string>> &graph,
                      map<node_t, long long> &memo) {
  string node;
  bool v_dac;
  bool v_fft;
  tie(node, v_dac, v_fft) = state;

  v_dac = node == "dac" ? true : v_dac;
  v_fft = node == "fft" ? true : v_fft;

  if (node == "out") {
    if (v_dac && v_fft) {
      return 1LL;
    } else {
      return 0LL;
    }
  }

  node_t check = make_tuple(node, v_dac, v_fft);

  if (memo.count(check)) {
    return memo[check];
  }

  long long total{0};
  for (const string &n : graph.at(node)) {
    total += count_paths(make_tuple(n, v_dac, v_fft), graph, memo);
  }

  memo[state] = total;
  return total;
}

int main() {
  unordered_map<string, vector<string>> graph{};
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
  }

  // print_graph(graph);

  /* dfs on graph */
  map<tuple<string, bool, bool>, long long> memo{};
  long long num_paths{
      count_paths(make_tuple("svr", false, false), graph, memo)};

  cout << num_paths << endl;
}
