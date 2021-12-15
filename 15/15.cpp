// 15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <set>
#include <queue>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define SQUARE_MAX   500
#define MATRIX_MAX     (SQUARE_MAX*SQUARE_MAX)
#define MULT 5

uint64_t fancyAlgorithm(void);
uint64_t fancyAlgorithm2(void);
int minDistance(void);
int getFancyMatrixAt(int row, int col);
int getFancyMatrixAt2(int row, int col);
uint32_t getColFromCoord(uint32_t x, uint32_t y);
void getCoordfromCol(uint32_t* x, uint32_t* y, uint32_t col);
bool neighbors(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);

uint32_t grid[SQUARE_MAX][SQUARE_MAX] = { 0 };
uint32_t x_max = 0;
uint32_t y_max = 0;
uint32_t x_max_div = 0;
uint32_t y_max_div = 0;

int matrix_len = 0;
int dist[MATRIX_MAX];
bool sptSet[MATRIX_MAX];

int main()
{
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            for (uint32_t i = 0;i < lineIn.length();i++)
            {
                grid[i][y_max] = lineIn.c_str()[i] - '0';
                x_max = max(x_max, i + 1);
            }
            y_max++;
        }
        else
        {
            break;
        }
    }

    //part1:
    /*matrix_len = x_max * y_max;
    uint64_t result = fancyAlgorithm();
    printf("%llu", result);*/

    //part2:
    x_max_div = x_max;
    y_max_div = y_max;
    x_max *= MULT;
    y_max *= MULT;

    matrix_len = x_max * y_max;
    uint64_t result = fancyAlgorithm2();
    printf("%llu", result);


}

int minDistance(void)
{
    int min = INT_MAX, min_index = 0;

    for (int v = 0; v < matrix_len; v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

uint64_t fancyAlgorithm(void)
{
    int src = 0;

    for (int i = 0; i < matrix_len; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }  

    dist[src] = 0;

    for (int count = 0; count < matrix_len - 1; count++)
    {
        int u = minDistance();
        sptSet[u] = true;

        for (int v = 0; v < matrix_len; v++)
        {
            if (!sptSet[v] && getFancyMatrixAt(u, v) && dist[u] != INT_MAX
                && dist[u] + getFancyMatrixAt(u, v) < dist[v])
            {
                dist[v] = dist[u] + getFancyMatrixAt(u, v);
            }
        }
    }

    return dist[matrix_len - 1];
}

uint64_t fancyAlgorithm2(void)
{
    int src = 0;

    for (int i = 0; i < matrix_len; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < matrix_len - 1; count++)
    {
        int u = minDistance();
        sptSet[u] = true;

        for (int v = 0; v < matrix_len; v++)
        {
            if (!sptSet[v] && getFancyMatrixAt2(u, v) && dist[u] != INT_MAX
                && dist[u] + getFancyMatrixAt2(u, v) < dist[v])
            {
                dist[v] = dist[u] + getFancyMatrixAt2(u, v);
            }
        }

        if (count % 5000 == 0)
        {
            printf("Iterations: %d\n", count);
        }
    }

    return dist[matrix_len - 1];
}

int getFancyMatrixAt(int row, int col)
{
    //test if neighbors
    uint32_t x0 = 0;
    uint32_t y0 = 0;
    uint32_t x1 = 0;
    uint32_t y1 = 0;

    getCoordfromCol(&x0, &y0, row);
    getCoordfromCol(&x1, &y1, col);

    if (neighbors(x0, y0, x1, y1))
    {
        return grid[x1][y1];
    }
    return 0;
}

int getFancyMatrixAt2(int row, int col)
{
    //test if neighbors
    uint32_t x0 = 0;
    uint32_t y0 = 0;
    uint32_t x1 = 0;
    uint32_t y1 = 0;

    getCoordfromCol(&x0, &y0, row);
    getCoordfromCol(&x1, &y1, col);

    if (neighbors(x0, y0, x1, y1))
    {
        uint64_t ret = grid[x1 % x_max_div][y1 % y_max_div] + (x1 / x_max_div) + (y1 / y_max_div);
        if (ret > 9)
        {
            ret = ret - 9;
        }
        return ret;
    }
    return 0;
}

void getCoordfromCol(uint32_t* x, uint32_t* y, uint32_t col)
{
    *x = col / x_max;
    *y = col % x_max;
}

bool neighbors(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
{
    if (x0 > 0)
    {
        if (x0 - 1 == x1 && y0 == y1)
        {
            return true;
        }
    }

    if (x0 < x_max - 1)
    {
        if (x0 + 1 == x1 && y0 == y1)
        {
            return true;
        }
    }

    if (y0 > 0)
    {
        if (y0 - 1 == y1 && x0 == x1)
        {
            return true;
        }
    }

    if (y0 < y_max - 1)
    {
        if (y0 + 1 == y1 && x0 == x1)
        {
            return true;
        }
    }

    return false;
}

uint32_t getColFromCoord(uint32_t x, uint32_t y)
{
    return ((x_max * y) + x);
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
