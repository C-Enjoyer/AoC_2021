// 20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define LUT_MAX 1000
#define PTS_MAX 10000

typedef struct pt
{
    int x, y;
}pt_t;

bool isLight(int xpos, int ypos);
void addLight(int xpos, int ypos);
void removeLight(int xpos, int ypos);
void doEnhancement(void);
void printImage(void);

bool lut[LUT_MAX] = { 0 };
uint32_t lut_num = 0;

pt_t pts[PTS_MAX] = { 0 };
uint32_t pts_num = 0;

pt_t pts_in[PTS_MAX] = { 0 };
uint32_t pts_in_num = 0;

int xmin = 0, xmax = 0;
int ymin = 0, ymax = 0;

int main()
{
    bool image = false;
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            if (!image)
            {
                for (uint32_t i = 0;i < lineIn.length();i++)
                {
                    lut[i] = (lineIn.c_str()[i] == '#') ? (true) : (false);
                }
                lut_num = lineIn.length();
            }
            else
            {
                for (uint32_t i = 0;i < lineIn.length();i++)
                {
                    if (lineIn.c_str()[i] == '#')
                    {
                        pts[pts_num].x = i;
                        pts[pts_num].y = ymax;
                        pts_num++;
                        pts_in[pts_in_num].x = i;
                        pts_in[pts_in_num].y = ymax;
                        pts_in_num++;
                    }
                }
                xmax = lineIn.length() - 1;
                ymax++;
            }
        }
        else
        {
            if (!image)
            {
                image = true;
            }
            else
            {
                break;
            }
        }
    }
    ymax--;

    //printImage();
    //printf("\n");
    printf("Lights: %d\n", pts_num);

    for (uint32_t i = 0;i < 2;i++)
    {
        doEnhancement();
        //printImage();
        //printf("\n");
        printf("Lights: %d\n", pts_num);
    }

    
    
}

void doEnhancement(void)
{
    xmin--;
    ymin--;
    xmax++;
    ymax++;

    for (int x = xmin;x <= xmax;x++)
    {
        for (int y = ymin;y <= ymax;y++)
        {
            uint32_t num = 0;

            if (isLight(x-1, y-1))      num |= (1 << 8);
            if (isLight(x, y-1))        num |= (1 << 7);
            if (isLight(x+1, y-1))      num |= (1 << 6);
            if (isLight(x-1, y))        num |= (1 << 5);
            if (isLight(x, y))          num |= (1 << 4);
            if (isLight(x+1, y))        num |= (1 << 3);
            if (isLight(x-1, y+1))      num |= (1 << 2);
            if (isLight(x, y+1))        num |= (1 << 1);
            if (isLight(x+1, y+1))      num |= (1 << 0);

            if (lut[num])
            {
                addLight(x, y);
            }
            else
            {
                removeLight(x, y);
            }
        }
    }




    for (uint32_t i = 0;i < PTS_MAX;i++)
    {
        pts_in[i].x = pts[i].x;
        pts_in[i].y = pts[i].y;
    }
    pts_in_num = pts_num;
}

void addLight(int xpos, int ypos)
{
    if (!isLight(xpos, ypos))
    {
        pts[pts_num].x = xpos;
        pts[pts_num].y = ypos;
        pts_num++;
    }
}

void removeLight(int xpos, int ypos)
{
    bool found = false;
    uint32_t foundIndex = 0;
    for (uint32_t i = 0;i < pts_num;i++)
    {
        if (pts[i].x == xpos && pts[i].y == ypos)
        {
            found = true;
            foundIndex = i;
            break;
        }
    }

    if (found)
    {
        pts_num--;
        for (uint32_t i = foundIndex;i < pts_num;i++)
        {
            pts[i] = pts[i + 1];
        }
    }
}

bool isLight(int xpos, int ypos)
{
    for (uint32_t i = 0;i < pts_in_num;i++)
    {
        if (pts_in[i].x == xpos && pts_in[i].y == ypos)
        {
            return true;
        }
    }
    return false;
}

void printImage(void)
{
    for (int y = ymin;y <= ymax;y++)
    {
        for (int x = xmin;x <= xmax;x++)
        {
            if (isLight(x, y))
            {
                printf("#");
            }
            else
            {
                printf(".");
            }
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
