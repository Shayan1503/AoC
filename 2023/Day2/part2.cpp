#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

void findMinimumSet(std::string turn, int *minimum_cubes)
{
    std::size_t cube_pos = turn.find(",");
    while (cube_pos != turn.npos)
    {
        std::string cube = turn.substr(0, cube_pos);

        std::size_t space_pos = cube.find(" ");
        int cube_no = stoi(cube.substr(0, space_pos));
        std::string cube_col = cube.substr(space_pos + 1);

        if (cube_col == "red" && cube_no > minimum_cubes[0])
        {
            minimum_cubes[0] = cube_no;
        }
        else if (cube_col == "green" && cube_no > minimum_cubes[1])
        {
            minimum_cubes[1] = cube_no;
        }
        else if (cube_col == "blue" && cube_no > minimum_cubes[2])
        {
            minimum_cubes[2] = cube_no;
        }

        turn = turn.substr(cube_pos + 2);
        cube_pos = turn.find(",");
    }

    std::size_t space_pos = turn.find(" ");
    int cube_no = stoi(turn.substr(0, space_pos));
    std::string cube_col = turn.substr(space_pos + 1);

    if (cube_col == "red" && cube_no > minimum_cubes[0])
    {
        minimum_cubes[0] = cube_no;
    }
    else if (cube_col == "green" && cube_no > minimum_cubes[1])
    {
        minimum_cubes[1] = cube_no;
    }
    else if (cube_col == "blue" && cube_no > minimum_cubes[2])
    {
        minimum_cubes[2] = cube_no;
    }
}

int getPower(std::string game)
{
    int minimum_cubes[] = {0, 0, 0};

    std::size_t turn_pos = game.find(";");
    while (turn_pos != game.npos)
    {
        std::string turn = game.substr(0, turn_pos);

        findMinimumSet(turn, minimum_cubes);

        game = game.substr(turn_pos + 2);
        turn_pos = game.find(";");
    }

    findMinimumSet(game, minimum_cubes);

    return minimum_cubes[0] * minimum_cubes[1] * minimum_cubes[2];
}

int sumOfPower(const std::string &filename)
{
    int sum = 0;
    std::string text;
    std::ifstream file(filename);

    while (std::getline(file, text))
    {
        std::size_t found = text.find(":");
        text = text.substr(found + 2);

        sum += getPower(text);
    }

    return sum;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    int total = sumOfPower("input.txt");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Answer: " << total << std::endl;
    std::cout << "Took " << duration.count() << " microseconds." << std::endl;
}