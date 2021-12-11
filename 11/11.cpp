// 11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define MAX_LINES     3000
#define MAX_ROW     100
#define MAX_COLUMN  100
#define STEPS       100

uint64_t doStep(void);
void doFlash(uint32_t row, uint32_t col);
void incrementEnergy(uint32_t row, uint32_t col);
void printEnergy(void);

uint32_t energy[MAX_ROW][MAX_COLUMN] = { 0 };
uint32_t energy_row = 0;
uint32_t energy_col = 0;
bool flashed[MAX_ROW][MAX_COLUMN] = { false };

using namespace std;

int main()
{
    uint32_t col_max = 0;
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            for (uint32_t i = 0;i < lineIn.length();i++)
            {
                energy[energy_row][energy_col] = lineIn.c_str()[i] - '0';
                energy_col++;
            }
            col_max = max(col_max, energy_col);
            energy_col = 0;
            energy_row++;
        }
        else
        {
            energy_col = col_max;
            break;
        }
    }

    //part1:
    /*
    uint64_t flashes = 0;

    for (uint32_t i = 0;i < STEPS;i++)
    {
        flashes += doStep();
    }

    printf("Result: %llu", flashes);

    */

    //part2:
    uint64_t step = 0;

    while(1)
    {
        uint64_t flashes = doStep();
        if (flashes == energy_row * energy_col)
        {
            step++;
            break;
        }
        step++;
    }

    printf("Result: %llu", step);
}

uint64_t doStep(void)
{
    uint64_t flashes = 0;

    for (uint32_t row = 0; row < energy_row; row++)
    {
        for (uint32_t col = 0; col < energy_col; col++)
        {
            incrementEnergy(row, col);
        }
    }

    while (1)
    {
        bool flashHappened = false;
        for (uint32_t row = 0; row < energy_row; row++)
        {
            for (uint32_t col = 0; col < energy_col; col++)
            {
                if (energy[row][col] > 9 && !flashed[row][col])
                {
                    flashHappened = true;
                    doFlash(row, col);
                    flashes++;
                }
            }
        }
        if (!flashHappened)
        {
            break;
        }
    }

    for (uint32_t row = 0; row < energy_row; row++)
    {
        for (uint32_t col = 0; col < energy_col; col++)
        {
            if (flashed[row][col])
            {
                flashed[row][col] = false;
                energy[row][col] = 0;
            }
        }
    }

    return flashes;
}

void doFlash(uint32_t row, uint32_t col)
{
    flashed[row][col] = true;

    if (row - 1 >= 0) //upper
    {
        incrementEnergy(row - 1, col);
    }
    if (row + 1 < energy_row) //lower
    {
        incrementEnergy(row + 1, col);
    }
    if (col - 1 >= 0) //left
    {
        incrementEnergy(row, col - 1);
    }
    if (col + 1 < energy_col) //right
    {
        incrementEnergy(row, col + 1);
    }

    if (row - 1 >= 0 && col - 1 >= 0) //upper left
    {
        incrementEnergy(row - 1, col - 1);
    }
    if (row - 1 >= 0 && col + 1 < energy_col) //upper right
    {
        incrementEnergy(row - 1, col + 1);
    }
    if (row + 1 < energy_row && col - 1 >= 0) //lower left
    {
        incrementEnergy(row + 1, col - 1);
    }
    if (row + 1 < energy_row && col + 1 < energy_col) //lower right
    {
        incrementEnergy(row + 1, col + 1);
    }
}

void incrementEnergy(uint32_t row, uint32_t col)
{
    if (flashed[row][col])
    {
        return;
    }
    if (energy[row][col] <= 9)
    {
        energy[row][col]++;
    }
}

void printEnergy(void)
{
    for (uint32_t row = 0; row < energy_row; row++)
    {
        for (uint32_t col = 0; col < energy_col; col++)
        {
            printf("%d", energy[row][col]);
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
