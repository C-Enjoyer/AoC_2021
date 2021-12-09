// 9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <windows.h>
#include <iosfwd>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define MAX_X     1000
#define MAX_Y      1000
#define BASIN_MAX  10000

using namespace std;

typedef struct coord
{
    int64_t x, y;

}coord_t;

bool checkLowPoint(uint64_t x, uint64_t y);
uint64_t checkSides(uint64_t x, uint64_t y);
void clear_Basin(void);
bool isInBasin(uint64_t x, uint64_t y);
void addToBasin(uint64_t x, uint64_t y);
void printInColor(void);


uint64_t numbers[MAX_X][MAX_Y] = { 0 };
coord_t basin[BASIN_MAX];
uint64_t basinNum = 0;

uint64_t basinSize[BASIN_MAX] = { 0 };
uint64_t basinSizeNum = 0;

uint64_t timesInBasin[MAX_X][MAX_Y] = { 0 };

uint64_t x_num = 0;
uint64_t y_num = 0;

uint64_t x_max = 0;
uint64_t y_max = 0;

int main()
{
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            for (uint64_t i = 0;i < lineIn.length();i++)
            {
                numbers[x_num][y_num] = lineIn.c_str()[i] - '0';
                x_num++;
                x_max = max(x_max, x_num);
            }
            y_num++;
            y_max = max(y_max, y_num);
            x_num = 0;
        }
        else
        {
            break;
        }
    }

    //part1
    /*
    uint64_t result = 0;

    for (uint64_t x = 0; x < x_max;x++)
    {
        for (uint64_t y = 0; y < y_max; y++)
        {
            uint64_t correct = 0;
            if (x <= 0 || numbers[x - 1][y] > numbers[x][y])
            {
                correct++;
            }
            if (x >= x_max - 1 || numbers[x + 1][y] > numbers[x][y])
            {
                correct++;
            }
            if (y <= 0 || numbers[x][y-1] > numbers[x][y])
            {
                correct++;
            }
            if (y >= y_max - 1 || numbers[x][y+1] > numbers[x][y])
            {
                correct++;
            }

            if (x == 6 && y == 4)
            {
                auto x = 0;
            }

            if(correct == 4)
            {
                result += (numbers[x][y] + 1);
            }
        }
    }

    printf("%llu", result);
    */
    
    
    //part 2
    uint64_t lowPoints = 0;
    for (uint64_t x = 0; x < x_max;x++)
    {
        for (uint64_t y = 0; y < y_max; y++)
        {
            clear_Basin();
            if (checkLowPoint(x, y))
            {
                lowPoints++;
                uint64_t result = checkSides(x, y);
                if (result == 69)
                {
                    auto z = 0;
                }
                
                printf("basin = %llu\n\n", result);
                basinSize[basinSizeNum] = result;
                basinSizeNum++;
            }
        }
    }

    printInColor();

    sort(basinSize, basinSize + basinSizeNum);

    uint64_t result = basinSize[basinSizeNum-1] * basinSize[basinSizeNum - 2] * basinSize[basinSizeNum - 3];
    
    printf("%llu", result);
}

uint64_t checkSides(uint64_t x, uint64_t y)
{
    uint64_t result = 1;

    if (numbers[x][y] == 9 || isInBasin(x, y))
    {
        return 0;
    }

    timesInBasin[x][y]++;

    addToBasin(x, y);
    timesInBasin[x][y]++;
    if (timesInBasin[x][y] >= 2)
    {
        auto z = 0;
    }

    printf("number[%llu][%llu] = %llu\n", x, y, numbers[x][y]);

    if (x > 0)
    {
        if (checkLowPoint(x - 1, y))
        {
            result += checkSides(x - 1, y);
        }
    }
    if (x < x_max - 1)
    {
        if (checkLowPoint(x + 1, y))
        {
            result += checkSides(x + 1, y);
        }
    }

    if (y > 0)
    {
        if (checkLowPoint(x, y - 1))
        {
            result += checkSides(x, y - 1);
        }
    }
    if (y < y_max - 1)
    {
        if (checkLowPoint(x, y + 1))
        {
            result += checkSides(x, y + 1);
        }
    }

    return result;
}

bool checkLowPoint(uint64_t x, uint64_t y)
{
    uint64_t correct = 0;
    if (x <= 0 || isInBasin(x - 1, y) || numbers[x - 1][y] >= numbers[x][y])
    {
        correct++;
    }
    if (x >= x_max - 1 || isInBasin(x + 1, y) || numbers[x + 1][y] >= numbers[x][y])
    {
        correct++;
    }
    if (y <= 0 || isInBasin(x, y-1) || numbers[x][y - 1] >= numbers[x][y])
    {
        correct++;
    }
    if (y >= y_max - 1 || isInBasin(x, y+1) || numbers[x][y + 1] >= numbers[x][y])
    {
        correct++;
    }

    if (correct == 4)
    {
        return true;
    }
    return false;
}

void clear_Basin(void)
{
    for (uint64_t i = 0;i < BASIN_MAX;i++)
    {
        basin[i].x = -1;
        basin[i].y = -1;
    }
    basinNum = 0;
}


bool isInBasin(uint64_t x, uint64_t y)
{
    for (uint64_t i = 0;i < basinNum;i++)
    {
        if (basin[i].x == x && basin[i].y == y)
        {
            return true;
        }
    }
    return false;
}

void addToBasin(uint64_t x, uint64_t y)
{
    basin[basinNum].x = x;
    basin[basinNum].y = y;
    basinNum++;
}

void printInColor(void)
{
    for (uint64_t y = 0;y < y_max;y++)
    {
        printf("%llu. ", y);
        for (uint64_t x = 0;x < x_max;x++)
        {
            if (timesInBasin[x][y] > 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
            }
            printf("%llu", numbers[x][y]);
        }
        printf("\n");
    }
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
