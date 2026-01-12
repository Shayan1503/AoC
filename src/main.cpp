#include "utils/graphics.hpp"
#include "utils/solution_registry.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  if (argc > 1) {
    if (argc < 4) {
      std::cerr << "Usage: " << argv[0] << " <Year> <Day> <Part> [Mode]"
                << std::endl;
      std::cerr << "  Mode: 0 = Test Input (default), 1 = Real Input"
                << std::endl;
      return 1;
    }

    int year = std::stoi(argv[1]);
    int day = std::stoi(argv[2]);
    int part = std::stoi(argv[3]);
    int mode = 1; // Default to real input mode
    if (argc >= 5) {
      mode = std::stoi(argv[4]);
    }

    auto solution = makeSolution(year, day, part, mode);
    if (!solution) {
      std::cerr << "Solution not found for Year " << year << " Day " << day
                << " Part " << part << std::endl;
      return 1;
    }

    std::cout << "Running Year " << year << " Day " << day << " Part " << part
              << " (Mode: " << (mode == 0 ? "Test" : "Real") << ")"
              << std::endl;
    auto result = solution->run();
    std::cout << "Result: " << result.first << std::endl;
    std::cout << "Time: " << result.second / 1000.0f << " microseconds"
              << std::endl;
    return 0;
  }

  Aoi ui;
  ui.run(getAvailableSolutions());

  return 0;
}
