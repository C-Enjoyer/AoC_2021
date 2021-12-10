// 10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#define MAX_LINE 1000
#define MAX_LINE_LEN 1000

using namespace std;

typedef enum level
{
    LEVEL0, //()
    LEVEL1, //[]
    LEVEL2, //{}
    LEVEL3, //<>

    LEVEL_NONE
}level_t;

level_t getLastOpen(uint32_t line, uint32_t from);

string lines[MAX_LINE];
uint32_t lines_num = 0;

bool openBracketCounted[MAX_LINE][MAX_LINE_LEN] = { false };

int main()
{
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            lines[lines_num] = lineIn;
            lines_num++;
        }
        else
        {
            break;
        }
    }

    //part1
    /*
    uint64_t result = 0;
    for (uint32_t line = 0; line < lines_num; line++)
    {
        for (uint32_t i = 0;i < lines[line].length();i++)
        {
            if (lines[line].c_str()[i] == ')')
            {
                if (getLastOpen(line, i) != LEVEL0)
                {
                    result += 3;
                    break;
                }
            }
            else if (lines[line].c_str()[i] == ']')
            {
                if (getLastOpen(line, i) != LEVEL1)
                {
                    result += 57;
                    break;
                }
            }
            else if (lines[line].c_str()[i] == '}')
            {
                if (getLastOpen(line, i) != LEVEL2)
                {
                    result += 1197;
                    break;
                }
            }
            else if (lines[line].c_str()[i] == '>')
            {
                if (getLastOpen(line, i) != LEVEL3)
                {
                    result += 25137;
                    break;
                }
            }
        }
    }

    printf("Result: %llu", result);
    */

    //part2:
    double results[MAX_LINE] = { 0 };
    uint32_t results_num = 0;
    for (uint32_t line = 0; line < lines_num; line++)
    {
        for (uint32_t i = 0;i < lines[line].length();i++)
        {
            if (lines[line].c_str()[i] == ')')
            {
                if (getLastOpen(line, i) != LEVEL0)
                {
                    break;
                }
            }
            else if (lines[line].c_str()[i] == ']')
            {
                if (getLastOpen(line, i) != LEVEL1)
                {
                    break;
                }
            }
            else if (lines[line].c_str()[i] == '}')
            {
                if (getLastOpen(line, i) != LEVEL2)
                {
                    break;
                }
            }
            else if (lines[line].c_str()[i] == '>')
            {
                if (getLastOpen(line, i) != LEVEL3)
                {
                    break;
                }
            }

            if (i == lines[line].length() - 1) // last character, string just incompleted
            {
                for (int32_t j = lines[line].length() - 1; j >= 0; j--)
                {
                    level_t res = getLastOpen(line, j);
                    if (res != LEVEL_NONE)
                    {
                        results[results_num] *= 5;
                        results[results_num] += (res + 1); // dirty but OK :)
                    }
                    else
                    {
                        results_num++;
                        break;
                    }
                }
            }
        }
    }

    sort(results, results + results_num);

    printf("Result: %f", results[results_num / 2]); // dirty but OK :)

}

level_t getLastOpen(uint32_t line, uint32_t from)
{
    for (int32_t i = from;i >= 0;i--)
    {
        if (openBracketCounted[line][i] == false)
        {
            if (lines[line].c_str()[i] == '(')
            {
                openBracketCounted[line][i] = true;
                from = (i > 0) ? (i - 1) : (0);
                return LEVEL0;
            }
            else if (lines[line].c_str()[i] == '[')
            {
                openBracketCounted[line][i] = true;
                from = (i > 0) ? (i - 1) : (0);
                return LEVEL1;
            }
            else if (lines[line].c_str()[i] == '{')
            {
                openBracketCounted[line][i] = true;
                from = (i > 0) ? (i - 1) : (0);
                return LEVEL2;
            }
            else if (lines[line].c_str()[i] == '<')
            {
                openBracketCounted[line][i] = true;
                from = (i > 0) ? (i - 1) : (0);
                return LEVEL3;
            }
        }
    }

    return LEVEL_NONE;
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
