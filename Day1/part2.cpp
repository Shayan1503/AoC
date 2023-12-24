#include <iostream>
#include <fstream>
#include <map>
#include <string>

std::map<std::string, int> ntoi = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}};

int getNumber(std::string str)
{
    int n = str.size();

    // finding the leftmost digit from substring
    std::size_t leftpos = str.size();
    int left = 0;
    for (auto i : ntoi)
    {
        std::size_t currpos = str.find(i.first);
        if (currpos != str.npos && currpos < leftpos)
        {
            leftpos = currpos;
            left = i.second;
        }
    }

    // checking if the leftmost digit is in alphanum form instead
    for (int i = 0; i < n; i++)
    {
        if (isdigit(str[i]) && i < leftpos)
        {
            left = str[i] - '0';
            break;
        }
    }

    // finding the rightmost digit from substring
    std::size_t rightpos = 0;
    int right = 0;
    for (auto i : ntoi)
    {
        std::size_t currpos = str.rfind(i.first);
        // cout << currpos << " " << i.first << " ";
        if (currpos != str.npos && currpos > rightpos)
        {
            rightpos = currpos;
            right = i.second;
        }
    }

    // checking if the rightmost digit is in alphanum form instead
    for (int i = n - 1; i >= 0; i--)
    {
        if (isdigit(str[i]) && i >= rightpos)
        {
            right = str[i] - '0';
            break;
        }
    }

    return left * 10 + right;
}

int getCalibratedSum(std::string filename)
{
    std::string text;
    std::ifstream file(filename);
    int sum = 0;

    while (getline(file, text))
    {
        int number = getNumber(text);
        std::cout << text << " - " << number << "\n";
        sum += number;
    }
    return sum;
}

int main()
{
    int sum = getCalibratedSum("input.txt");
    std::cout << "Answer:" << sum << std::endl;
}