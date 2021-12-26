// 24.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_INS	400
#define START ('9')
#define END ('1')

bool doInsForNum(uint8_t* arr);

int64_t w = 0, x = 0, y = 0, z=0;
int nums[3][14] = { 0 };
int64_t lastRes = 0;

int main()
{
	uint8_t lineNum = 0;
	uint8_t column = 0;
	while (1)
	{
		string lineIn;
		getline(cin, lineIn);
		if (lineIn.length())
		{
			//5,15
			if (lineNum == 5)
			{
				nums[0][column] = stoi(lineIn.substr(6));
			}
			else if (lineNum == 15)
			{
				nums[1][column] = stoi(lineIn.substr(6));
			}
			else if (lineNum == 4)
			{
				nums[2][column] = stoi(lineIn.substr(6));
			}

			if (lineNum < 18 - 1)
			{
				lineNum++;
			}
			else
			{
				lineNum = 0;
				column++;
			}
		}
		else
		{
			break;
		}
	}

	//part 1:
	/*

	uint8_t startnum[15] = { '9', '9', '1', '1', '1', '1','1', '1', '1', '1', '1', '1', '1','1','\0'};
	bool first = true;

	uint8_t num[15] = { 0 };
	uint64_t steps = 0;
	uint64_t number = 0;



	for(num[0] = START; num[0] >= END; num[0]--) for (num[1] = START; num[1] >= END; num[1]--) for (num[2] = START; num[2] >= END; num[2]--) for (num[3] = START; num[3] >= END; num[3]--) for (num[4] = START; num[4] >= END; num[4]--) for (num[5] = START; num[5] >= END; num[5]--) for (num[6] = START; num[6] >= END; num[6]--)
		for (num[7] = START; num[7] >= END; num[7]--) for (num[8] = START; num[8] >= END; num[8]--) for (num[9] = START; num[9] >= END; num[9]--) for (num[10] = START; num[10] >= END; num[10]--) for (num[11] = START; num[11] >= END; num[11]--) for (num[12] = START; num[12] >= END; num[12]--) for (num[13] = START; num[13] >= END; num[13]--)
		{
			if (first)
			{
				for (uint8_t i = 0;i < 15;i++)
				{
					num[i] = startnum[i];
				}
				first = false;
			}
			if (doInsForNum(num))
			{
				number = stoull((char*)num, NULL, 10);
				goto found;
			}
			steps++;
			if (steps % 100000000 == 0)
			{
				printf("Number: %llu\n", stoull((char*)num, NULL, 10));
				printf("Steps: %llu\n", steps);
				printf("LastRes: %d\n", lastRes);
			}
		}


found:
	printf("Found number! %llu", number);

	*/

	//part2:

	uint8_t startnum[15] = { '3', '1', '5', '1', '9', '1','1', '1', '1', '1', '1', '1', '1','1','\0' };
	bool first = true;

	uint8_t num[15] = { 0 };
	uint64_t steps = 0;
	uint64_t number = 0;



	for (num[0] = END; num[0] <= START; num[0]++) for (num[1] = END; num[1] <= START; num[1]++) for (num[2] = END; num[2] <= START; num[2]++) for (num[3] = END; num[3] <= START; num[3]++) for (num[4] = END; num[4] <= START; num[4]++) for (num[5] = END; num[5] <= START; num[5]++) for (num[6] = END; num[6] <= START; num[6]++)
		for (num[7] = END; num[7] <= START; num[7]++) for (num[8] = END; num[8] <= START; num[8]++) for (num[9] = END; num[9] <= START; num[9]++) for (num[10] = END; num[10] <= START; num[10]++) for (num[11] = END; num[11] <= START; num[11]++)for (num[12] = END; num[12] <= START; num[12]++) for (num[13] = END; num[13] <= START; num[13]++)
		{
			if (first)
			{
				for (uint8_t i = 0;i < 15;i++)
				{
					num[i] = startnum[i];
				}
				first = false;
			}
			if (doInsForNum(num))
			{
				number = stoull((char*)num, NULL, 10);
				goto found;
			}
			steps++;
			if (steps % 100000000 == 0)
			{
				printf("Number: %llu\n", stoull((char*)num, NULL, 10));
				printf("Steps: %llu\n", steps);
				printf("LastRes: %d\n", lastRes);
			}
		}


found:
	printf("Found number! %llu", number);
}

bool doInsForNum(uint8_t *arr)
{
	w = 0;
	x = 0;
	y = 0;
	z = 0;
	for (uint8_t i = 0;i < 14;i++)
	{
		w = arr[i] - '0';
		x = 0;
		x += z;
		if (x > 0)
		{
			x = x % 26;
		}
		z = z / nums[2][i];
		x += nums[0][i];
		x = (x == w) ? (1) : (0);
		x = (x == 0) ? (1) : (0);
		y = 0;
		y += 25;
		y *= x;
		y += 1;
		z *= y;
		y = 0;
		y += w;
		y += nums[1][i];
		y *= x;
		z += y;
	}

	lastRes = z;

	return z == 0;
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
