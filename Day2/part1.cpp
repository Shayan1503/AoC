#include <iostream>
#include <fstream>
#include <vector>
#define RED 12
#define GREEN 13
#define BLUE 14

bool isPossibleCube(std::string cube)
{
    std::size_t space_pos = cube.find(" ");
    std::string number = cube.substr(0, space_pos);
    std::string color = cube.substr(space_pos + 1);

    if (color == "red" && stoi(number) > RED)
        return false;
    if (color == "green" && stoi(number) > GREEN)
        return false;
    if (color == "blue" && stoi(number) > BLUE)
        return false;

    return true;
}

bool isPossibleTurn(std::string turn)
{
    std::size_t cube_pos = turn.find(",");

    while (cube_pos != turn.npos)
    {
        if (!isPossibleCube(turn.substr(0, cube_pos)))
            return false;

        turn = turn.substr(cube_pos + 2);
        cube_pos = turn.find(",");
    }
    // for the single cube left
    return isPossibleCube(turn);
}

bool isPossibleGame(std::string game)
{
    std::size_t turn_pos = game.find(";");

    while (turn_pos != game.npos)
    {
        if (!isPossibleTurn(game.substr(0, turn_pos)))
            return false;
        game = game.substr(turn_pos + 2);
        turn_pos = game.find(";");
    }

    // for the last turn
    return isPossibleTurn(game);
}

int sumPossibleGames(std::string filename)
{
    int sum = 0;
    std::string text;
    std::ifstream file(filename);
    int game = 1;

    while (std::getline(file, text))
    {
        std::size_t found = text.find(":");
        text = text.substr(found + 2);

        if (isPossibleGame(text))
            sum += game;

        game++;
    }

    return sum;
}

int main()
{
    int sum_of_ids = sumPossibleGames("input.txt");
    std::cout << "Answer: " << sum_of_ids << std::endl;
}