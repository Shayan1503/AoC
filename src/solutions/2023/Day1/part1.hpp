#pragma once
#include "../../../utils/solution_registry.cpp"
#include "../../solution.hpp"

class Day1Part1_2023 : public Solution {
public:
  Day1Part1_2023() : Solution(2023, 1, 1) {}
  Day1Part1_2023(int mode) : Solution(2023, 1, 1, mode) {}

  int solve() override {
    int sum = 0;
    for (const auto &text : input) {
      int n = text.size();
      char first = ' ', last = ' ';
      for (int i = 0; i < n; i++) {
        if (isdigit(text[i])) {
          first = text[i];
          break;
        }
      }

      for (int i = n - 1; i >= 0; i--) {
        if (isdigit(text[i])) {
          last = text[i];
          break;
        }
      }

      int number = (first - '0') * 10 + (last - '0');
      sum += number;
    }

    return sum;
  }
};

REGISTER_SOLUTION(Day1Part1_2023, 2023, 1, 1);
