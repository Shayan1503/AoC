#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>

const std::map<std::string, int> color_numbers = {{"red", 12}, {"green", 13}, {"blue", 14}};

bool isPossibleCube(const std::string &cube) {
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

int sumPossibleGames(const std::string &filename) {
    int sum = 0;
    std::ifstream file(filename);
    std::string text;
    int game = 1;

    while (std::getline(file, text)) {
        std::size_t found = text.find(":");
        text = text.substr(found + 2);

        if (isPossibleGame(text))
            sum += game;

        game++;
    }

    return sum;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    int sum_of_ids = sumPossibleGames("input.txt");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Answer: " << sum_of_ids << std::endl;
    std::cout << "Took " << duration.count() << " microseconds." << std::endl;
}
