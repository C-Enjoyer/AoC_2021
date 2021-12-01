// 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

#define MAX_NUM 5000

int main()
{
    uint32_t numbers[MAX_NUM] = { 0 };
    uint32_t numbers_num = 0;

    uint32_t sums[MAX_NUM] = { 0 };
    uint32_t sums_num = 0;

    uint32_t increased = 0;
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            numbers[numbers_num] = atoi(line.c_str());
            numbers_num++;
        }
        else
        {
            break;
        }
    }

    /*for (uint32_t i = 0;i < numbers_num-1;i++)
    {
        if (numbers[i + 1] > numbers[i])
        {
            increased++;
        }
    }

    printf("Increased: %d", increased);
    */

    for(uint32_t i = 0;i < numbers_num; i++)
    {
        sums[sums_num] = numbers[i] + numbers[i + 1] + numbers[i + 2];
        sums_num++;
    }

    for (uint32_t i = 0;i < sums_num -1;i++)
    {
        if (sums[i + 1] > sums[i])
        {
            increased++;
        }
    }

    printf("Increased: %d", increased);



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
