#include "../../../utils/solution_registry.hpp"
#include "../../solution.hpp"

class Day1Part2_2025 : public Solution {
public:
    Day1Part2_2025() : Solution(2025, 1, 2) {}
    Day1Part2_2025(int mode) : Solution(2025, 1, 2, mode) {}

    std::size_t solve() override {
        int counter = 0;
        int current_pos = 50;
        int next_pos = 0;

        for (const auto &text: input) {
            char direction = text[0];
            int distance = std::stoi(text.substr(1));
            
            for(int i = 0; i < distance; i++) {
                if(direction == 'L') {
                    current_pos--;
                } else {
                    current_pos++;
                }

                if(current_pos % 100 == 0) {
                    counter++;
                }

                current_pos = (current_pos + 100) % 100;
            }
        }

        return counter;
    }
};

REGISTER_SOLUTION(Day1Part2_2025, 2025, 1, 2);