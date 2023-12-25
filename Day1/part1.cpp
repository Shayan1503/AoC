#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

int getSum(const std::string &filename)
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
        // std::cout << text << " - " << number << "\n";
        sum += number;
    }

    return sum;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    int total = getSum("input.txt");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Answer: " << total << std::endl;
    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}