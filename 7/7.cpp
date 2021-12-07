// 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define MAX_NUM     3000

using namespace std;

uint32_t getFuel(uint32_t start, uint32_t end);

uint32_t numbers[MAX_NUM] = { 0 };
uint32_t numbers_num = 0;
uint32_t number_max = 0;

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            string cur = "";
            int32_t lastSeperator = -1;
            for (uint32_t i = 0;i < line.length();i++)
            {
                if (line[i] == ',')
                {
                    cur = line.substr(lastSeperator + 1, i - (lastSeperator + 1));
                    lastSeperator = i;
                    numbers[numbers_num] = atoi(cur.c_str());
                    numbers_num++;

                    number_max = max(number_max, numbers[numbers_num-1]);
                }
                else if (i == line.length() - 1)
                {
                    cur = line.substr(lastSeperator + 1);
                    numbers[numbers_num] = atoi(cur.c_str());
                    numbers_num++;
                    number_max = max(number_max, numbers[numbers_num-1]);
                }
            }
        }
        else
        {
            break;
        }
    }

    //part 1
    /*uint32_t best = UINT32_MAX;

    for (uint32_t test = 0;test < number_max;test++)
    {
        uint32_t dif = 0;
        for (uint32_t number = 0;number < numbers_num;number++)
        {
            dif += abs((double)test - (double)numbers[number]);
        }
        best = min(best, dif);
    }

    printf("%d", best);*/

    //part 2
    uint32_t best = UINT32_MAX;

    for (uint32_t test = 0;test < number_max;test++)
    {
        uint32_t dif = 0;
        for (uint32_t number = 0;number < numbers_num;number++)
        {
            dif += getFuel(test, numbers[number]);
        }
        best = min(best, dif);
    }

    printf("%d", best);

}

//if you like gauss more
uint32_t getFuel(uint32_t start, uint32_t end)
{
    uint32_t dif = max(start, end) - min(start, end);
    return (dif * dif + dif) / 2;
}

/* if you are into the brute-force-thing
uint32_t getFuel(uint32_t start, uint32_t end)
{
    uint32_t _start = min(start, end);
    uint32_t _end = max(start, end);
    uint32_t result = 0;
    for (uint32_t i = _start;i <= _end;i++)
    {
        result += (i - _start);
    }
    return result;
}*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
