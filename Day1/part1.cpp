#include <iostream>
#include <fstream>
#include <string>

int getSum(std::string filename)
{
    std::string text;
    std::ifstream file(filename);
    int sum = 0;

    while (getline(file, text))
    {
        int n = text.size();
        char first = ' ';
        char last = ' ';
        for (int i = 0; i < n; i++)
        {
            if (isdigit(text[i]))
            {
                first = text[i];
                break;
            }
        }

        for (int i = n - 1; i >= 0; i--)
        {
            if (isdigit(text[i]))
            {
                last = text[i];
                break;
            }
        }

        int number = (first - '0') * 10 + (last - '0');
        std::cout << text << " - " << number << "\n";
        sum += number;
    }

    return sum;
}

int main()
{
    int total = getSum("input.txt");
    std::cout << "Answer: " << total << std::endl;
}