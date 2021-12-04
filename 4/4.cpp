// 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#define MAXLINE 5000
#define MAX_NUM 500
#define MAX_GRID 500

using namespace std;

typedef struct bingo_grid
{
    uint32_t data[5][5]; //row, column
}bingo_grid_t;

bool checkBingo(uint32_t numberTill, uint32_t curGridNum);
bool isInNumbers(uint32_t number, uint32_t numberTill);
uint32_t unmarkedSum(uint32_t curGridNum, uint32_t numberTill);

uint32_t numbers[MAX_NUM] = { 0 };
uint32_t numbers_num = 0;
bingo_grid_t grid[MAX_GRID] = { {0} , {0} }; //he's watching you
uint32_t grid_num = 0;



int main()
{
    bool isFirstLine = true;
    bool lastLineEmpty = false;
    bool firstEmptyLine = true;
    uint32_t cur_row = 0;
    while (1)
    {
        string line;
        getline(cin, line);


        if (line.length())
        {
            if (isFirstLine) //numbers
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
                isFirstLine = false;
            }
            else //grid
            {
                lastLineEmpty = false;
                sscanf(line.c_str(), "%d %d %d %d %d",  &grid[grid_num].data[cur_row][0],
                                                        &grid[grid_num].data[cur_row][1],
                                                        &grid[grid_num].data[cur_row][2],
                                                        &grid[grid_num].data[cur_row][3],
                                                        &grid[grid_num].data[cur_row][4]);
                cur_row++;
            }
        }
        else
        {
            if (!lastLineEmpty) //new grid or first empty line
            {
                if (firstEmptyLine)
                {
                    firstEmptyLine = false;
                    lastLineEmpty = true;
                }
                else
                {
                    lastLineEmpty = true;
                    cur_row = 0;
                    grid_num++;
                }
            }
            else //end
            {
                break;
            }
        }
    }

    //part 1
    /*bool found = false;
    uint32_t winning_grid_num = 0;
    uint32_t winning_number = 0;
    uint32_t winning_number_num = 0;
    uint32_t sumUnmarked = 0;

    for (uint32_t number=0;number < numbers_num;number++)
    {
        for (uint32_t curGridNum = 0;curGridNum < grid_num;curGridNum++)
        {
            if (checkBingo(number, curGridNum))
            {
                winning_grid_num = curGridNum;
                winning_number = numbers[number];
                winning_number_num = number;
                found = true;
                break;
            }
        }
        if (found)
        {
            break;
        }
    }

    if (found)
    {
        sumUnmarked = unmarkedSum(winning_grid_num, winning_number_num);

        printf("Result: %d", sumUnmarked * winning_number);
    }*/

    //part2

    bool hasBingo[MAX_GRID] = { false };
    uint32_t bingos = 0;
    uint32_t losing_grid_num = 0;
    uint32_t winning_number_num = 0;
    uint32_t winning_number = 0;
    bool found = false;
    uint32_t sumUnmarked = 0;

    for (uint32_t number = 0;number < numbers_num;number++)
    {
        for (uint32_t curGridNum = 0;curGridNum < grid_num;curGridNum++)
        {
            if (!hasBingo[curGridNum])
            {
                if (checkBingo(number, curGridNum))
                {
                    hasBingo[curGridNum] = true;
                    bingos++;
                    if (bingos == grid_num)
                    {
                        losing_grid_num = curGridNum;
                        winning_number = numbers[number];
                        winning_number_num = number;
                        found = true;
                        break;
                    }
                }
            }
        }
        if (found)
        {
            break;
        }
    }

    if (found)
    {
        sumUnmarked = unmarkedSum(losing_grid_num, winning_number_num);

        printf("Result: %d", sumUnmarked* winning_number);
    }





}

bool checkBingo(uint32_t numberTill, uint32_t curGridNum)
{
    for (uint32_t row = 0;row < 5;row++)
    {
        for (uint32_t rowElem = 0;rowElem < 5;rowElem++)
        {
            if (isInNumbers(grid[curGridNum].data[row][rowElem], numberTill))
            {
                if (rowElem == 5 - 1)
                {
                    return true;
                }
            }
            else
            {
                break;
            }
        }
    }

    for (uint32_t column = 0;column < 5;column++)
    {
        for (uint32_t columnElem = 0;columnElem < 5;columnElem++)
        {
            if (isInNumbers(grid[curGridNum].data[columnElem][column], numberTill))
            {
                if (columnElem == 5 - 1)
                {
                    return true;
                }
            }
            else
            {
                break;
            }
        }
    }

    return false;
}

bool isInNumbers(uint32_t number, uint32_t numberTill)
{
    for (uint32_t i = 0;i < numberTill + 1;i++)
    {
        if (numbers[i] == number)
        {
            return true;
        }
    }

    return false;
}

uint32_t unmarkedSum(uint32_t curGridNum, uint32_t numberTill)
{
    uint32_t sum = 0;
    for (uint32_t row = 0;row < 5;row++)
    {
        for (uint32_t column = 0;column < 5;column++)
        {
            uint32_t cur_num = grid[curGridNum].data[row][column];
            if (!isInNumbers(cur_num, numberTill))
            {
                sum += cur_num;
            }
        }
    }

    return sum;
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
