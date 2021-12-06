// 6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>


#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define MAX_NUM     500
#define MAX_DAYS    9
//part1
//#define CYCLES    80
//part2
#define CYCLES      256

using namespace std;

uint64_t numbers[MAX_NUM] = { 0 };
uint64_t numbers_num = 0;

uint64_t daysLeft[MAX_DAYS] = { 0 };

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
                }
                else if (i == line.length() - 1)
                {
                    cur = line.substr(lastSeperator + 1);
                    numbers[numbers_num] = atoi(cur.c_str());
                    numbers_num++;
                }
            }
        }
        else
        {
            break;
        }
    }

    for (uint64_t number = 0;number < numbers_num;number++)
    {
        daysLeft[numbers[number]]++;
    }


    for (uint64_t cycle = 0; cycle < CYCLES;cycle++)
    {
        uint64_t fromDay0 = 0;
        for (uint64_t day = 0;day < MAX_DAYS;day++)
        {
            if (day == 0)
            {
                daysLeft[6] += daysLeft[0];
                daysLeft[8] += daysLeft[0];
                fromDay0 += daysLeft[0];
                daysLeft[0] = 0;
            }
            else if(day == 6 || day == 8)
            {
                daysLeft[day - 1] += (daysLeft[day] - fromDay0);
                daysLeft[day] = fromDay0;
            }
            else
            {
                daysLeft[day - 1] += daysLeft[day];
                daysLeft[day] = 0;
            }
        }
    }

    uint64_t total = 0;

    for (uint64_t day = 0;day < MAX_DAYS;day++)
    {
        total += daysLeft[day];
    }

    printf("Result: %llu", total);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
