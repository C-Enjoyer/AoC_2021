// 21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;
void doTurn(uint32_t p1pos, uint32_t p2pos, uint32_t p1s, uint32_t p2s, bool isP1, uint64_t pathReachedTimes, uint64_t* p1w, uint64_t* p2w);
uint32_t doDice(uint32_t pos, uint32_t num);
uint32_t combinationsFromPoints(uint8_t p);


uint32_t p1 = 6, p2 = 8;
//part 1:
/*uint32_t p1p = 0, p2p = 0;
uint32_t die = 1;*/

int main()
{
    //part1:
    /*
    uint64_t result = 0;
    while (1)
    {
        p1 += 3 * (die + 1);
        die += 3;

        p1 %= 10;
        if (p1 == 0) p1 = 10;

        p1p += p1;

        if (p1p >= 1000)
        {
            result = p2p * (die - 1);
            break;
        }

        p2 += 3 * (die + 1);
        die += 3;

        p2 %= 10;
        if (p2 == 0) p2 = 10;

        p2p += p2;

        if (p2p >= 1000)
        {
            result = p1p * (die - 1);
            break;
        }
    }

    printf("Result: %llu", result);
    */

    //part2:
    uint64_t p1w = 0;
    uint64_t p2w = 0;

    doTurn(p1, p2, 0, 0, true, 1, &p1w, &p2w);

    uint64_t res = max(p1w, p2w);

    printf("Result: %llu", res);


}

void doTurn(uint32_t p1pos, uint32_t p2pos, uint32_t p1s, uint32_t p2s, bool isP1, uint64_t pathReachedTimes, uint64_t* p1w, uint64_t* p2w)
{
    if (isP1)
    {
        for (uint8_t i = 3; i <= 9; i++) //only these numbers can be dices with 3 rolls
        {
            uint32_t nextp1pos = p1pos;
            nextp1pos = doDice(nextp1pos, i);
            uint32_t newP1Score = p1s + nextp1pos;
            if (newP1Score >= 21)
            {
                *p1w += combinationsFromPoints(i) * pathReachedTimes;
            }
            else
            {
                doTurn(nextp1pos, p2pos, newP1Score, p2s, !isP1, combinationsFromPoints(i) * pathReachedTimes, p1w, p2w);
            } 
        }
    }
    else
    {
        for (uint8_t i = 3; i <= 9; i++) //only these numbers can be dices with 3 rolls
        {
            uint32_t nextp2pos = p2pos;
            nextp2pos = doDice(nextp2pos, i);
            uint32_t newP2Score = p2s + nextp2pos;
            if (newP2Score >= 21)
            {
                *p2w += combinationsFromPoints(i) * pathReachedTimes;
            }
            else
            {
                doTurn(p1pos, nextp2pos, p1s, newP2Score, !isP1, combinationsFromPoints(i) * pathReachedTimes, p1w, p2w);
            }
        }
    }
}


uint32_t doDice(uint32_t pos, uint32_t num)
{
    pos += num;
    pos %= 10;
    if (pos == 0) pos = 10;

    return pos;
}

uint32_t combinationsFromPoints(uint8_t p)
{
    switch (p)
    {
        case 3: return 1;
        case 4: return 3;
        case 5: return 6;
        case 6: return 7;
        case 7: return 6;
        case 8: return 3;
        case 9: return 1;
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
