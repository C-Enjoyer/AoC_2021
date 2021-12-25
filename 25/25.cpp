// 25.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define XMAX 300
#define YMAX 300
#define GRIDSIZE (XMAX*YMAX)

bool doStep(void);
void printGrid(void);

char grid[XMAX][YMAX] = { 0 };
uint32_t xmax = 0;
uint32_t ymax = 0;

uint32_t fromX[GRIDSIZE] = { 0 }, fromY[GRIDSIZE]{ 0 };
uint32_t toX[GRIDSIZE] = { 0 }, toY[GRIDSIZE]{ 0 };
uint32_t numMoves = 0;

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
				grid[i][ymax] = lineIn.c_str()[i];
			}
			xmax = lineIn.length();
			ymax++;
		}
		else
		{
			break;
		}
	}

	//part1:
	/*uint64_t steps = 0;

	while (1)
	{
		steps++;
		if (!doStep())
		{
			break;
		}
		//printf("%llu:\n", steps);
		//printGrid();
		//printf("\n\n");
	}

	printf("Result: %llu", steps);*/

	//part2:

	
}

bool doStep(void)
{
	bool didMove = false;
	numMoves = 0;

	for (uint32_t y = 0; y < ymax; y++)
	{
		for (uint32_t x = 0; x < xmax; x++)
		{
			if (grid[x][y] == '>')
			{
				uint32_t nextx = (x + 1 < xmax) ? (x + 1) : (0);
				if (grid[nextx][y] == '.')
				{
					fromX[numMoves] = x;
					toX[numMoves] = nextx;
					fromY[numMoves] = y;
					numMoves++;
					didMove = true;
				}
			}
		}
	}

	for (uint32_t i = 0;i < numMoves;i++)
	{
		grid[fromX[i]][fromY[i]] = '.';
		grid[toX[i]][fromY[i]] = '>';
	}

	numMoves = 0;



	for (uint32_t x = 0; x < xmax; x++)
	{
		for (uint32_t y = 0; y < ymax; y++)
		{
			if (grid[x][y] == 'v')
			{
				uint32_t nexty = (y + 1 < ymax) ? (y + 1) : (0);
				if (grid[x][nexty] == '.')
				{
					fromY[numMoves] = y;
					toY[numMoves] = nexty;
					fromX[numMoves] = x;
					numMoves++;
					didMove = true;
				}
			}
		}
	}

	for (uint32_t i = 0;i < numMoves;i++)
	{
		grid[fromX[i]][fromY[i]] = '.';
		grid[fromX[i]][toY[i]] = 'v';
	}

	return didMove;
}

void printGrid(void)
{
	for (uint32_t y = 0; y < ymax; y++)
	{
		for (uint32_t x = 0; x < xmax; x++)
		{
			printf("%c", grid[x][y]);
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
