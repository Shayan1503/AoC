#pragma once
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
  int year;
  int day;
  int part;

  Solution(const int year, const int day, const int part)
      : year(year), day(day), part(part) {}
  Solution(const int year, const int day, const int part, const int mode)
      : year(year), day(day), part(part), mode(mode) {}

  virtual ~Solution() = default;

  int getYear() const { return year; }
  int getDay() const { return day; }
  int getPart() const { return part; }

  virtual int solve() {
    std::cout << "Solving..." << std::endl;
    return 0;
  };

  std::string getFullFilename() {
    if (mode == 0) {
      return "../src/solutions/" + std::to_string(year) + "/Day" +
             std::to_string(day) + "/test" + std::to_string(part) + ".txt";
    }

    return "../src/solutions/" + std::to_string(year) + "/Day" +
           std::to_string(day) + "/input.txt";
  }

  void parseInput() {
    std::string filename = getFullFilename();
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
      input.push_back(line);
    }
  }

  std::pair<int, long long> run() {
    parseInput();

    auto start = std::chrono::high_resolution_clock::now();
    int result = solve();
    auto end = std::chrono::high_resolution_clock::now();

    long long time_taken =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();

    std::pair<int, long long> output{result, time_taken};
    return output;
  }

protected:
  std::vector<std::string> input;
  int mode;
};
