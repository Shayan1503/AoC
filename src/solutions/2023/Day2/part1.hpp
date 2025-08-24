#pragma once
#include "../../../utils/solution_registry.cpp"
#include "../../solution.hpp"
#include <map>

class Day2Part1_2023 : public Solution {
public:
  Day2Part1_2023() : Solution(2023, 2, 1) {}
  Day2Part1_2023(int mode) : Solution(2023, 2, 1, mode) {}

  bool isPossibleCube(const std::string &cube) const {
    std::istringstream iss(cube);
    std::string number, color;
    iss >> number >> color;
    return stoi(number) <= color_numbers.at(color);
  }

  bool isPossibleTurn(const std::string &turn) {
    std::istringstream iss(turn);
    std::string cube;
    while (std::getline(iss, cube, ',')) {
      if (!isPossibleCube(cube))
        return false;
    }
    return true;
  }

  bool isPossibleGame(const std::string &game) {
    std::istringstream iss(game);
    std::string turn;
    while (std::getline(iss, turn, ';')) {
      if (!isPossibleTurn(turn))
        return false;
    }
    return true;
  }

  int solve() override {
    int sum = 0;
    int game = 1;

    for (auto &line : input) {
      std::size_t found = line.find(":");
      line = line.substr(found + 2);

      if (isPossibleGame(line))
        sum += game;

      game++;
    }

    return sum;
  }

private:
  const std::map<std::string, int> color_numbers = {
      {"red", 12}, {"green", 13}, {"blue", 14}};
};

REGISTER_SOLUTION(Day2Part1_2023, 2023, 2, 1);
