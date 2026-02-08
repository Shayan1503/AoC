#include "../../../utils/solution_registry.hpp"
#include "../../solution.hpp"
#include "string_view"

class Day2Part1_2025 : public Solution {
public:
    Day2Part1_2025() : Solution(2025, 2, 1) {}
    Day2Part1_2025(int mode) : Solution(2025, 2, 1, mode) {}

    bool isInvalidID(long id) {
        std::string text_id = std::to_string(id);
        std::size_t id_length = text_id.length();

        if(id_length % 2 == 1) {
            return false;
        }

        for(std::size_t i = 0; i < id_length / 2; i++) {
            if(text_id[i] != text_id[id_length / 2 + i]) {
                return false;
            }
        }

        return true;
    }

    std::size_t sumOfInvalidIDs(std::string_view text_range) {
        std::size_t sum = 0;

        std::size_t dash_pos = text_range.find('-');
        long range_start = std::stol(std::string(text_range.substr(0, dash_pos)));
        long range_finish = std::stol(std::string(text_range.substr(dash_pos + 1, text_range.length() - dash_pos)));

        for(long i = range_start; i <= range_finish; i++) {
            if(isInvalidID(i)) {
                sum += i;
            }
        }

        return sum;
    }

    std::size_t solve() override {
        if(input.size() == 0) {
            return 0;
        }
        
        std::size_t sum = 0;
        const std::string& text = input[0];
        std::size_t begin = 0;

        for(std::size_t i = 0; i < text.length(); i++) {
            if(text[i] == ',') {
                sum += sumOfInvalidIDs(std::string_view(text).substr(begin, i - begin));
                begin = i + 1;
            }
        }
        sum += sumOfInvalidIDs(std::string_view(text).substr(begin));

        return sum;
    }
};

REGISTER_SOLUTION(Day2Part1_2025, 2025, 2, 1)