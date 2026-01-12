#include "../../../utils/solution_registry.hpp"
#include "../../solution.hpp"
#include <string>

class Day1Part1_2025 : public Solution {
public:
    Day1Part1_2025() : Solution(2025, 1, 1) {}
    Day1Part1_2025(int mode) : Solution(2025, 1, 1, mode) {}

    int solve() override {
        int counter = 0;
        int current_pos = 50;

        for (const auto &text: input) {
            char direction = text[0];
            int distance = std::stoi(text.substr(1));
            
            if (direction == 'L') {
                current_pos = current_pos - distance;
            } else {
                current_pos = current_pos + distance;
            }
            current_pos = (current_pos + 100) % 100;
            
            if (current_pos == 0) {
                counter++;
            }
        }

        return counter;
    }
};

REGISTER_SOLUTION(Day1Part1_2025, 2025, 1, 1);