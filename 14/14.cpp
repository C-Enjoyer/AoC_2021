// 14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_REACT   400
#define MAX_LETTER  200

typedef struct react
{
    char from[2];
    char insert;
    uint32_t to[MAX_REACT*2];
    uint32_t to_num;
    uint64_t num;
}react_t;

typedef struct letter
{
    char c;
    uint64_t num;
}letter_t;

void doCycle(void);
void getReacts(void);
void getLetters(void);
void addLetter(char c);
void addToLetter(char c, uint64_t num);

string start = "";
react_t reacts[MAX_REACT] = { 0 };
uint32_t reacts_num = 0;
letter_t letters[MAX_LETTER] = { 0 };
uint32_t letters_num = 0;

int main()
{
    bool isStart = true;
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            if (isStart)
            {
                start = lineIn;
            }
            else
            {
                reacts[reacts_num].from[0] = lineIn.c_str()[0];
                reacts[reacts_num].from[1] = lineIn.c_str()[1];
                reacts[reacts_num].insert = lineIn.c_str()[6];
                reacts_num++;
            }
        }
        else
        {
            if (isStart)
            {
                isStart = false;
            }
            else
            {
                break;
            }
        }
    }

    getReacts();
    getLetters();
    
    for (uint32_t i = 0;i < start.length() - 1;i++)
    {
        addToLetter(start.c_str()[i], 1);
        for (uint32_t j = 0;j < reacts_num;j++)
        {
            if (start.c_str()[i] == reacts[j].from[0] && start.c_str()[i + 1] == reacts[j].from[1])
            {
                reacts[j].num++;
            }
        }
    }
    addToLetter(start.c_str()[start.length() - 1], 1);


    //part 1:
    /*for (uint32_t i = 0;i < 10;i++)
    {
        doCycle();
    }*/

    //part 2:
    for (uint32_t i = 0;i < 40;i++)
    {
        doCycle();
    }

    uint64_t num_min = UINT64_MAX;
    uint64_t num_max = 0;
    uint64_t length = 0;

    for (uint32_t i = 0;i < letters_num;i++)
    {
        num_min = min(num_min, letters[i].num);
        num_max = max(num_max, letters[i].num);
    }

    printf("Result: %llu", num_max - num_min);

}

void doCycle(void)
{
    uint64_t add[MAX_REACT] = { 0 };

    for (uint32_t i = 0;i < reacts_num;i++)
    {
        if (reacts[i].num)
        {
            addToLetter(reacts[i].insert, reacts[i].num);
            for (uint32_t j = 0;j < reacts[i].to_num;j++)
            {
                add[reacts[i].to[j]] += reacts[i].num;
            }
            reacts[i].num = 0;
        }
    }

    for (uint32_t i = 0;i < reacts_num;i++)
    {
        reacts[i].num += add[i];
    }
}

void getReacts(void)
{
    for (uint32_t i = 0;i < reacts_num;i++)
    {
        for (uint32_t j = 0;j < reacts_num;j++)
        {
            if ((reacts[i].from[0] == reacts[j].from[0] && reacts[i].insert == reacts[j].from[1]) ||
                (reacts[i].insert == reacts[j].from[0] && reacts[i].from[1] == reacts[j].from[1])
                )
            {
                reacts[i].to[reacts[i].to_num] = j;
                reacts[i].to_num++;
            }
        }
    }
}

void getLetters(void)
{
    for (uint32_t i = 0;i < reacts_num;i++)
    {
        addLetter(reacts[i].from[0]);
        addLetter(reacts[i].from[1]);
        addLetter(reacts[i].insert);
    }
}

void addLetter(char c)
{
    bool found = false;
    for (uint32_t i = 0;i < letters_num;i++)
    {
        if (letters[i].c == c)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        letters[letters_num].c = c;
        letters_num++;
    }
}

void addToLetter(char c, uint64_t num)
{
    for (uint32_t i = 0;i < letters_num;i++)
    {
        if (letters[i].c == c)
        {
            letters[i].num += num;
            break;
        }
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
