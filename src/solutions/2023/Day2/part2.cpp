
#include "../../../utils/solution_registry.hpp"
#include "../../solution.hpp"

class Day2Part2_2023 : public Solution {
public:
  Day2Part2_2023() : Solution(2023, 2, 2) {}
  Day2Part2_2023(int mode) : Solution(2023, 2, 2, mode) {}

  void findMinimumSet(std::string turn, int *minimum_cubes) {
    std::size_t cube_pos = turn.find(",");
    while (cube_pos != turn.npos) {
      std::string cube = turn.substr(0, cube_pos);

      std::size_t space_pos = cube.find(" ");
      int cube_no = stoi(cube.substr(0, space_pos));
      std::string cube_col = cube.substr(space_pos + 1);

      if (cube_col == "red" && cube_no > minimum_cubes[0]) {
        minimum_cubes[0] = cube_no;
      } else if (cube_col == "green" && cube_no > minimum_cubes[1]) {
        minimum_cubes[1] = cube_no;
      } else if (cube_col == "blue" && cube_no > minimum_cubes[2]) {
        minimum_cubes[2] = cube_no;
      }

      turn = turn.substr(cube_pos + 2);
      cube_pos = turn.find(",");
    }

    std::size_t space_pos = turn.find(" ");
    int cube_no = stoi(turn.substr(0, space_pos));
    std::string cube_col = turn.substr(space_pos + 1);

    if (cube_col == "red" && cube_no > minimum_cubes[0]) {
      minimum_cubes[0] = cube_no;
    } else if (cube_col == "green" && cube_no > minimum_cubes[1]) {
      minimum_cubes[1] = cube_no;
    } else if (cube_col == "blue" && cube_no > minimum_cubes[2]) {
      minimum_cubes[2] = cube_no;
    }
  }

  int getPower(std::string game) {
    int minimum_cubes[] = {0, 0, 0};

    std::size_t turn_pos = game.find(";");
    while (turn_pos != game.npos) {
      std::string turn = game.substr(0, turn_pos);

      findMinimumSet(turn, minimum_cubes);

      game = game.substr(turn_pos + 2);
      turn_pos = game.find(";");
    }

    findMinimumSet(game, minimum_cubes);

    return minimum_cubes[0] * minimum_cubes[1] * minimum_cubes[2];
  }

  int solve() override {
    int sum = 0;

    for (auto &line : input) {
      std::size_t found = line.find(":");
      line = line.substr(found + 2);

      sum += getPower(line);
    }

    return sum;
  }
};

REGISTER_SOLUTION(Day2Part2_2023, 2023, 2, 2);
