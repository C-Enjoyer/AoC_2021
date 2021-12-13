// 13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define X_MAX   2000
#define Y_MAX   2000
#define FOLD_MAX 20
#define GRIDS 2

typedef enum sym
{
    SYM_NONE = 0,
    SYM_DOT
}sym_t;

typedef struct fold
{
    uint32_t num;
    bool isX;
}fold_t;

void copyGrid(void);
uint32_t getNum(void);
uint32_t getOthNum(void);
void doFold(uint32_t fold_num);
uint64_t getDots(void);
void printGrid(void);

sym_t grid[GRIDS][X_MAX][Y_MAX] = { SYM_NONE };
uint32_t x_max[GRIDS] = { 0 };
uint32_t y_max[GRIDS] = { 0 };
bool isGrid0 = true;

fold_t folds[FOLD_MAX] = { 0 };
uint32_t folds_num = 0;

int main()
{
    bool isFold = false;
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            if (!isFold)
            {
                uint32_t x = 0, y = 0;
                sscanf(lineIn.c_str(), "%d,%d", &x, &y);

                x_max[0] = max(x_max[0], x + 1);
                y_max[0] = max(y_max[0], y + 1);

                grid[0][x][y] = SYM_DOT;
                grid[1][x][y] = SYM_DOT;
            }
            else
            {
                if (lineIn.find('x') != string::npos)
                {
                    folds[folds_num].isX = true;
                }
                string num = lineIn.substr(lineIn.find('=') + 1);
                folds[folds_num].num = atoi(num.c_str());
                folds_num++;
            }
        }
        else
        {
            if (!isFold)
            {
                isFold = true;
            }
            else
            {
                x_max[1] = x_max[0];
                y_max[1] = y_max[0];
                break;
            }
        }
    }

    //part1
    /*doFold(0);
    uint64_t result = getDots();
    printf("%llu", result);*/

    //part2
    for (uint32_t i = 0;i < folds_num;i++)
    {
        doFold(i);
    }

    printGrid();
}

void doFold(uint32_t fold_num)
{
    if (folds[fold_num].isX)
    {
        if (folds[fold_num].num != x_max[getNum()] / 2)
        {
            return;
        }
    }
    else
    {
        if (folds[fold_num].num != y_max[getNum()] / 2)
        {
            return;
        }
    }

    if (folds[fold_num].isX)
    {
        for (uint32_t y = 0; y < y_max[getNum()]; y++)
        {
            for (uint32_t x = folds[fold_num].num; x < x_max[getNum()]; x++)
            {
                if (grid[getNum()][x][y] == SYM_DOT)
                {
                    uint32_t xCopy = folds[fold_num].num - (x - folds[fold_num].num);
                    grid[getOthNum()][xCopy][y] = SYM_DOT;
                }
            }
        }
        x_max[getOthNum()] = folds[fold_num].num;
    }
    else
    {
        for (uint32_t x = 0; x < x_max[getNum()]; x++)
        {
            for (uint32_t y = folds[fold_num].num; y < y_max[getNum()]; y++)
            {
                if (grid[getNum()][x][y] == SYM_DOT)
                {
                    uint32_t yCopy = folds[fold_num].num - (y - folds[fold_num].num);
                    grid[getOthNum()][x][yCopy] = SYM_DOT;
                }
            }
        }
        y_max[getOthNum()] = folds[fold_num].num;
    }

    isGrid0 = !isGrid0;
    copyGrid();
}


uint64_t getDots(void)
{
    uint64_t dots = 0;
    for (uint32_t x = 0; x < x_max[getNum()]; x++)
    {
        for (uint32_t y = 0; y < y_max[getNum()]; y++)
        {
            if (grid[getNum()][x][y] == SYM_DOT)
            {
                dots++;
            }
        }
    }
    return dots;
}

void printGrid(void)
{
    for (uint32_t y = 0; y < y_max[getNum()]; y++)
    {
        for (uint32_t x = 0; x < x_max[getNum()]; x++)
        {
            if (grid[getNum()][x][y] == SYM_DOT)
            {
                printf("%c", 219);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void copyGrid(void)
{
    for (uint32_t x = 0; x < x_max[getNum()]; x++)
    {
        for (uint32_t y = 0; y < y_max[getNum()]; y++)
        {
            grid[getOthNum()][x][y] = grid[getNum()][x][y];
        }
    }
    x_max[getOthNum()] = x_max[getNum()];
    y_max[getOthNum()] = y_max[getNum()];
}

uint32_t getNum(void)
{
    if (isGrid0)
    {
        return 0;
    }
    return 1;
}

uint32_t getOthNum(void)
{
    if (isGrid0)
    {
        return 1;
    }
    return 0;
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
