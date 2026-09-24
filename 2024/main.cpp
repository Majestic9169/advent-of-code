#include "util.hpp"

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

struct Config {
  int day = -1;  // -1 means all days
  int part = -1; // -1 means both parts
  bool show_help = false;
};

void print_help(std::string_view program_name) {
  std::cout << std::format(
      "Advent of Code Solution Runner\n\n"
      "Usage: {} [options]\n\n"
      "Options:\n"
      "  -d, --day DAY    Specify day (1-25, default: all days)\n"
      "  -p, --part PART  Specify part (1-2, default: both parts)\n"
      "  -h, --help       Show this help message\n",
      program_name);
}

Config parse_args(int argc, char *argv[]) {
  Config config;
  for (int i = 1; i < argc; ++i) {
    std::string_view arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      config.show_help = true;
      return config;
    }
    if ((arg == "-d" || arg == "--day") && i + 1 < argc) {
      config.day = std::stoi(argv[++i]);
    } else if ((arg == "-p" || arg == "--part") && i + 1 < argc) {
      config.part = std::stoi(argv[++i]);
    }
  }
  return config;
}

std::string read_file(std::filesystem::path path) {
  std::ifstream file(path, std::ios::in | std::ios::binary);
  if (!file)
    return "";

  file.seekg(0, std::ios::end);
  std::string content(file.tellg(), '\0');
  file.seekg(0, std::ios::beg);
  file.read(content.data(), content.size());
  return content;
}

template <typename Func>
DayResult run_timed_part(int day, int part, std::string_view input,
                         const Func &func) {
  auto start = std::chrono::high_resolution_clock::now();
  std::string answer = func(input);
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> duration = end - start;
  return DayResult{day, part, answer, duration.count()};
}

void print_results(const std::vector<DayResult> &results) {
  std::cout << "\n+======+======+==================+===============+\n";
  std::cout << "| Day  | Part |      Answer      |   Time (ms)   |\n";
  std::cout << "+======+======+==================+===============+\n";

  double total_time = 0.0;
  for (const auto &res : results) {
    std::cout << std::format("| {:>4} | {:>4} | {:>16} | {:>13.3f} |\n",
                             res.day, res.part, res.answer, res.time_ms);
    total_time += res.time_ms;
  }

  std::cout << "+======+======+==================+===============+\n";
  std::cout << std::format("| Total time: {:>32.3f} ms |\n", total_time);
  std::cout << "+======+======+==================+===============+\n\n";
}

int main(int argc, char *argv[]) {
  Config config = parse_args(argc, argv);

  if (config.show_help) {
    print_help(argv[0]);
    return 0;
  }

  auto solutions = SolutionRegistry::instance().solutions();

  // Sort registered solutions chronologically by day
  std::sort(solutions.begin(), solutions.end(),
            [](const auto &a, const auto &b) { return a.day < b.day; });

  std::vector<DayResult> results;

  for (const auto &sol : solutions) {
    if (config.day != -1 && config.day != sol.day) {
      continue;
    }

    std::string input_path = std::format("day{:02d}.txt", sol.day);
    std::string input = read_file(input_path);

    if (input.empty()) {
      std::cerr << std::format(
          "Warning: Could not read input at '{}'. Skipping day {}.\n",
          input_path, sol.day);
      continue;
    }

    std::cout << "found file " << input_path << std::endl;

    if (config.part == -1 || config.part == 1) {
      results.push_back(run_timed_part(sol.day, 1, input, sol.part1));
    }
    if (config.part == -1 || config.part == 2) {
      results.push_back(run_timed_part(sol.day, 2, input, sol.part2));
    }
  }

  if (results.empty()) {
    std::cout
        << "\nNo solutions were executed. Check your filters or input files.\n";
  } else {
    print_results(results);
  }

  return 0;
}
