#pragma once
#include "../../../utils/solution_registry.cpp"
#include "../../solution.hpp"
#include <map>

class Day1Part2_2023 : public Solution {
public:
  Day1Part2_2023() : Solution(2023, 1, 2, 0) {}
  explicit Day1Part2_2023(int mode) : Solution(2023, 1, 2, mode) {}

  int getNumber(std::string str) {
    int n = str.size();

    // finding the leftmost digit from substring
    std::size_t leftpos = str.size();
    int left = 0;
    for (auto i : ntoi) {
      std::size_t currpos = str.find(i.first);
      if (currpos != str.npos && currpos < leftpos) {
        leftpos = currpos;
        left = i.second;
      }
    }

    // checking if the leftmost digit is in alphanum form instead
    for (int i = 0; i < n; i++) {
      if (isdigit(str[i]) && i < leftpos) {
        left = str[i] - '0';
        break;
      }
    }

    // finding the rightmost digit from substring
    std::size_t rightpos = 0;
    int right = 0;
    for (auto i : ntoi) {
      std::size_t currpos = str.rfind(i.first);
      if (currpos != str.npos && currpos > rightpos) {
        rightpos = currpos;
        right = i.second;
      }
    }

    // checking if the rightmost digit is in alphanum form instead
    for (int i = n - 1; i >= 0; i--) {
      if (isdigit(str[i]) && i >= rightpos) {
        right = str[i] - '0';
        break;
      }
    }

    return left * 10 + right;
  }

  int solve() override {
    int sum = 0;

    for (const auto &line : input) {
      int number = getNumber(line);
      sum += number;
    }

    return sum;
  }

private:
  std::map<std::string, int> ntoi = {{"one", 1},   {"two", 2},   {"three", 3},
                                     {"four", 4},  {"five", 5},  {"six", 6},
                                     {"seven", 7}, {"eight", 8}, {"nine", 9}};
};

REGISTER_SOLUTION(Day1Part2_2023, 2023, 1, 2);
