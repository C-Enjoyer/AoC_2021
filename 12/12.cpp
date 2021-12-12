// 12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#define MAX_KNOTS 30

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

typedef struct knot
{
    string name;
    bool isBig;
    uint32_t pathTo[MAX_KNOTS];
    uint32_t pathToNum;
}knot_t;

uint32_t getNumFromName(string s);
uint64_t getPathsToEnd(uint32_t fromKnot, bool* knotUsed);
uint64_t getPathsToEnd2(uint32_t fromKnot, bool* knotUsed);
bool isSomeKnotUsedTwice(uint32_t* knotUsed);

knot_t knots[MAX_KNOTS] = { "", false, {0}, 0 };
uint32_t knots_num = 0;

bool knotUsedG[MAX_KNOTS] = { 0 };
bool knotIsUsedTwice = false;
uint32_t knotUsedTwice = 0;

int main()
{
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            string p1, p2;

            for (uint32_t i = 0;i < lineIn.length();i++)
            {
                if (lineIn.c_str()[i] == '-')
                {
                    p1 = lineIn.substr(0, i);
                    p2 = lineIn.substr(i + 1);
                    break;
                }
            }
            
            bool In1 = false;
            bool In2 = false;
            for (uint32_t i = 0;i < knots_num;i++)
            {
                if (knots[i].name == p1)
                {
                    In1 = true;
                }
                else if (knots[i].name == p2)
                {
                    In2 = true;
                }
            }

            //totally overcomplicating stuff here... :)
            if (!In1 && !In2)
            {
                knots[knots_num].name = p1;
                knots[knots_num].isBig = isupper(p1.c_str()[0]);
                knots[knots_num].pathToNum++;
                knots_num++;

                knots[knots_num].name = p2;
                knots[knots_num].isBig = isupper(p2.c_str()[0]);
                knots[knots_num].pathToNum++;
                knots_num++;

                knots[knots_num-2].pathTo[0] = getNumFromName(p2);
                knots[knots_num-1].pathTo[0] = getNumFromName(p1);
            }
            else if (!In1)
            {
                knots[knots_num].name = p1;
                knots[knots_num].isBig = isupper(p1.c_str()[0]);
                knots[knots_num].pathTo[0] = getNumFromName(p2);
                knots[knots_num].pathToNum++;
                knots_num++;

                knots[getNumFromName(p2)].pathTo[knots[getNumFromName(p2)].pathToNum] = getNumFromName(p1);
                knots[getNumFromName(p2)].pathToNum++;
            }
            else if (!In2)
            {
                knots[knots_num].name = p2;
                knots[knots_num].isBig = isupper(p2.c_str()[0]);
                knots[knots_num].pathTo[0] = getNumFromName(p1);
                knots[knots_num].pathToNum++;
                knots_num++;

                knots[getNumFromName(p1)].pathTo[knots[getNumFromName(p1)].pathToNum] = getNumFromName(p2);
                knots[getNumFromName(p1)].pathToNum++;
            }
            else
            {
                knots[getNumFromName(p2)].pathTo[knots[getNumFromName(p2)].pathToNum] = getNumFromName(p1);
                knots[getNumFromName(p2)].pathToNum++;

                knots[getNumFromName(p1)].pathTo[knots[getNumFromName(p1)].pathToNum] = getNumFromName(p2);
                knots[getNumFromName(p1)].pathToNum++;
            }
        }
        else
        {
            break;
        }
    }

    //part1
    /*uint32_t start = getNumFromName("start");

    uint64_t result = getPathsToEnd(start, knotUsedG);

    printf("%llu", result);*/

    //part2

    uint32_t start = getNumFromName("start");

    uint64_t result = getPathsToEnd2(start, knotUsedG);

    printf("%llu", result);
}

uint32_t getNumFromName(string s)
{
    for (uint32_t i = 0;i < knots_num;i++)
    {
        if (knots[i].name == s)
        {
            return i;
        }
    }
    return 0;
}

uint64_t getPathsToEnd2(uint32_t fromKnot, bool* knotUsed)
{
    uint64_t paths = 0;

    if (knots[fromKnot].name == "end")
    {
        return 1;
    }

    for (uint32_t i = 0;i < knots[fromKnot].pathToNum;i++)
    {
        uint32_t actKnot = knots[fromKnot].pathTo[i];
        if (!knotUsed[actKnot] || !knotIsUsedTwice)
        {
            if (knots[actKnot].name != "start")
            {
                if (!knots[actKnot].isBig)
                {
                    if (knotUsed[actKnot])
                    {
                        knotIsUsedTwice = true;
                        knotUsedTwice = actKnot;
                    }
                    else
                    {
                        knotUsed[actKnot] = true;
                    }
                }
                uint64_t newPaths = 0;
                newPaths = getPathsToEnd2(actKnot, knotUsed);
                if (knotIsUsedTwice && knotUsedTwice == actKnot)
                {
                    knotIsUsedTwice = false;
                    knotUsedTwice = 0;
                }
                else
                {
                    knotUsed[actKnot] = false;
                }
                paths += newPaths;
            }
        }
    }

    return paths;
}

uint64_t getPathsToEnd(uint32_t fromKnot, bool* knotUsed)
{
    uint64_t paths = 0;

    if (knots[fromKnot].name == "end")
    {
        return 1;
    }

    if (!knots[fromKnot].isBig)
    {
        knotUsed[fromKnot] = true;
    }

    for (uint32_t i = 0;i < knots[fromKnot].pathToNum;i++)
    {
        uint32_t actKnot = knots[fromKnot].pathTo[i];
        if (!knotUsed[actKnot])
        {
            if (!knots[actKnot].isBig)
            {
                knotUsed[actKnot] = true;
            }
            uint64_t newPaths = 0;
            newPaths = getPathsToEnd(actKnot, knotUsed);
            if (newPaths > 0)
            {
                knotUsed[actKnot] = false;
            }
            paths += newPaths;
        }
    }

    knotUsed[fromKnot] = false;

    return paths;
}

bool isSomeKnotUsedTwice(uint32_t* knotUsed)
{
    for (uint32_t i = 0;i < knots_num;i++)
    {
        if (knotUsed[i] >= 2)
        {
            return true;
        }
    }
    return false;
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
