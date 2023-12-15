#include <iostream>
#include <fstream>
#include <map>

using namespace std;

map<string, int> ntoi = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}};

int getNumber(string str)
{
    int n = str.size();

    // finding the leftmost digit from substring
    size_t leftpos = str.size();
    int left = 0;
    for (auto i : ntoi)
    {
        size_t currpos = str.find(i.first);
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
    size_t rightpos = 0;
    int right = 0;
    for (auto i : ntoi)
    {
        size_t currpos = str.rfind(i.first);
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

int getCalibratedSum(string filename)
{
    string text;
    ifstream file(filename);
    int sum = 0;

    while (getline(file, text))
    {
        int number = getNumber(text);
        cout << text << " - " << number << "\n";
        sum += number;
    }
    return sum;
}

int main()
{
    int sum = getCalibratedSum("input.txt");
    cout << "Answer:" << sum << endl;
}