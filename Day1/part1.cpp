#include <iostream>
#include <fstream>

using namespace std;

int getSum(string filename)
{
    string text;
    ifstream file(filename);
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
        cout << text << " - " << number << "\n";
        sum += number;
    }

    return sum;
}

int main()
{
    int total = getSum("input.txt");
    cout << "Answer: " << total << endl;
}