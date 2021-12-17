// 17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#define Y_MAX 500
#define Y_MIN -500

using namespace std;

bool hitsArea(int x, int y);
bool isInArea(int x, int y);

int xstart=0, xend=0, ystart=0, yend=0;

int ymax = 0;

int main()
{
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length()) //overcomplicating parsing
        {
            uint8_t num = 0;
            uint32_t start = 0;
            for (uint32_t i = 0;i < lineIn.length();i++)
            {
                if (lineIn.c_str()[i] == '=')
                {
                    start = i + 1;
                }
                else if (lineIn.c_str()[i] == '.')
                {
                    if (num == 0)
                    {
                        xstart = atoi(lineIn.substr(start, i-start).c_str());
                        num++;
                    }
                    else if (num == 1)
                    {
                        start = i + 1;
                    }
                    else if (num == 2)
                    {
                        ystart = atoi(lineIn.substr(start, i - start).c_str());
                        num++;
                    }
                    else
                    {
                        start = i + 1;
                        break;
                    }
                }
                else if (lineIn.c_str()[i] == ',')
                {
                    if (num == 1)
                    {
                        xend = atoi(lineIn.substr(start, i - start).c_str());
                        num++;
                    }
                }
            }

            yend = atoi(lineIn.substr(start).c_str());
        }
        else
        {
            break;
        }
    }

    uint32_t vels = 0;

    for (int y = Y_MIN;y <= Y_MAX;y++)
    {
        for (int x = 0;x <= xend;x++)
        {
            if (hitsArea(x, y))
            {
                vels++;
            }
        }
    }

    //part1:
    //printf("Result %d", ymax);

    //part2:
    printf("Result %lu", vels);
}

bool hitsArea(int x, int y)
{
    int curx = 0, cury = 0;
    int velx = x, vely = y;
    bool posx = x > 0;
    uint32_t cnt = 1;
    int ymax_cur = 0;
    while (1)
    {
        curx += velx;
        cury += vely;

        ymax_cur = max(ymax_cur, cury);

        if (curx > xend || cury < ystart)
        {
            return false;
        }

        if (isInArea(curx, cury))
        {
            ymax = max(ymax, ymax_cur);
            return true;
        }

        vely--;
        if (velx != 0)
        {
            if (posx) velx--;
            else velx++;
        }
        cnt++;
    }

    return false;
}

bool isInArea(int x, int y)
{
    return (xstart <= x && x <= xend && ystart <= y && y <= yend);
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
