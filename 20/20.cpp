// 20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

void doStep(void);
uint32_t count_on(void);

#define SIZE 210
#define X0 55
#define Y0 55
#define LUT_SIZE 512

char lut[LUT_SIZE + 1];
char grid[2][SIZE][SIZE];
uint8_t gi; /* index of currently active grid */
int xmin = X0, xmax = X0 - 1, ymin = Y0, ymax = Y0 - 1;

int main()
{
	int len;
	bool first = true;
	while (1)
	{
		string lineIn;
		getline(cin, lineIn);
		if (lineIn.length())
		{
			if (first)
			{
				strcpy(lut, lineIn.c_str());
				len = strlen(lut);
				for (uint32_t i = 0; i < len; i++)
				{
					lut[i] = lut[i] == '#';
				}
				// account for empty cell rule
				if (lut[0])
				{
					memset(grid[1], 1, sizeof(grid[1]));
				}
			}
			else
			{
				strcpy(&grid[0][ymax + 1][X0], lineIn.c_str());
				len = (int)strlen(&grid[0][ymax + 1][X0]);
				xmax = max(xmax, X0 + len - 1);
				ymax++;
				for (uint32_t i = 0; i < len; i++)
				{
					grid[0][ymax][X0 + i] = grid[0][ymax][X0 + i] == '#';
				}
			}
		}
		else
		{
			if (first)
			{
				first = false;
			}
			else
			{
				break;
			}
		}
	}

	//part1:
	/*
	for (uint32_t i = 0; i < 2; i++)
	{ 
		doStep();
	}*/

	//part2:
	for (uint32_t i = 0; i < 50; i++)
	{
		doStep();
	}
	
	uint32_t result = count_on();
	printf("Result : %d", result);
	


	/*for (uint32_t i = 0; i < 50; i++)
	{
		doStep();
	} 
	p2 = count_on();*/
}

void doStep(void)
{
	int x, y;

	for (y = ymin - 1; y <= ymax + 1; y++)
	{
		for (x = xmin - 1; x <= xmax + 1; x++)
		{
			grid[!gi][y][x] = lut[
			grid[gi][y - 1][x - 1] << 8 |
			grid[gi][y - 1][x] << 7 |
			grid[gi][y - 1][x + 1] << 6 |
			grid[gi][y][x - 1] << 5 |
			grid[gi][y][x] << 4 |
			grid[gi][y][x + 1] << 3 |
			grid[gi][y + 1][x - 1] << 2 |
			grid[gi][y + 1][x] << 1 |
			grid[gi][y + 1][x + 1]];
		}
	}



	gi = !gi;
	xmin--; xmax++;
	ymin--; ymax++;
}

uint32_t count_on(void)
{
	uint32_t num = 0;

	for (int y = ymin; y <= ymax; y++)
	{
		for (int x = xmin; x <= xmax; x++)
		{
			num += grid[gi][y][x];
		}
	}

	return num;
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
