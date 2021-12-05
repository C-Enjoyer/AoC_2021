// 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#define MAXLINE 5000
#define MAXGRID 2000

using namespace std;

typedef struct line
{
    uint32_t x1, y1, x2, y2;
}line_t;

void printGrid(uint32_t xmax, uint32_t ymax);
bool isDiagonal(line_t curline);


line_t lines[MAXLINE] = { 0 };
uint32_t lines_num = 0;
uint32_t grid[MAXGRID][MAXGRID] = { 0 };

int main()
{
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);


        if (lineIn.length())
        {
            sscanf(lineIn.c_str(), "%d,%d -> %d,%d", &lines[lines_num].x1, &lines[lines_num].y1, &lines[lines_num].x2, &lines[lines_num].y2);
            lines_num++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*uint32_t twoPoints = 0;
    uint32_t xmax = 0;
    uint32_t ymax = 0;

    for (uint32_t curline = 0; curline < lines_num; curline++)
    {
        if (lines[curline].x1 == lines[curline].x2)
        {
            uint32_t lowery = min(lines[curline].y1, lines[curline].y2);
            uint32_t uppery = max(lines[curline].y1, lines[curline].y2);
            for (uint32_t y = lowery; y < uppery + 1;y++)
            {
                grid[lines[curline].x1][y]++;
            }
        }
        else if(lines[curline].y1 == lines[curline].y2)
        {
            uint32_t lowerx = min(lines[curline].x1, lines[curline].x2);
            uint32_t upperx = max(lines[curline].x1, lines[curline].x2);
            for (uint32_t x = lowerx; x < upperx + 1;x++)
            {
                grid[x][lines[curline].y1]++;
            }

        }

        xmax = max(xmax, lines[curline].x1);
        xmax = max(xmax, lines[curline].x2);
        ymax = max(ymax, lines[curline].y1);
        ymax = max(ymax, lines[curline].y2);
    }

    //printGrid(xmax, ymax);

    for (uint32_t x = 0;x < MAXGRID;x++)
    {
        for (uint32_t y = 0;y < MAXGRID;y++)
        {
            if (grid[x][y] >= 2)
            {
                twoPoints++;
            }
        }
    }

    printf("Result: %d", twoPoints);*/



    //part 2
    uint32_t twoPoints = 0;

    for (uint32_t curline = 0; curline < lines_num; curline++)
    {
        if (lines[curline].x1 == lines[curline].x2)
        {
            uint32_t lowery = min(lines[curline].y1, lines[curline].y2);
            uint32_t uppery = max(lines[curline].y1, lines[curline].y2);
            for (uint32_t y = lowery; y < uppery + 1;y++)
            {
                grid[lines[curline].x1][y]++;
                if (grid[lines[curline].x1][y] == 2)
                {
                    twoPoints++;
                }
            }
        }
        else if (lines[curline].y1 == lines[curline].y2)
        {
            uint32_t lowerx = min(lines[curline].x1, lines[curline].x2);
            uint32_t upperx = max(lines[curline].x1, lines[curline].x2);
            for (uint32_t x = lowerx; x < upperx + 1;x++)
            {
                grid[x][lines[curline].y1]++;
                if (grid[x][lines[curline].y1] == 2)
                {
                    twoPoints++;
                }
            }

        }
        else if (isDiagonal(lines[curline]))
        {
            uint32_t xstart = lines[curline].x1;
            uint32_t xend = lines[curline].x2;
            uint32_t ystart = lines[curline].y1;
            uint32_t yend = lines[curline].y2;

            bool xUp = (xstart < xend);
            bool yUp = (ystart < yend);
            uint32_t x = xstart;
            uint32_t y = ystart;

            while (1)
            {
                grid[x][y]++;
                if (grid[x][y] == 2)
                {
                    twoPoints++;
                }

                if (xUp)
                {
                    x++;
                    if (x == xend + 1)
                    {
                        break;
                    }
                }
                else
                {
                    x--;
                    if (x == xend - 1)
                    {
                        break;
                    }
                }

                if (yUp)
                {
                    y++;
                }
                else
                {
                    y--;
                }
            }
        }
    }

    printf("Result: %d", twoPoints);

    
}

void printGrid(uint32_t xmax, uint32_t ymax)
{
    for(uint32_t y = 0;y < ymax+1;y++)
    {
        for (uint32_t x = 0;x < xmax+1;x++)
        {
            if (grid[x][y] == 0)
            {
                printf(".");
            }
            else
            {
                printf("%d", grid[x][y]);
            }
        }
        printf("\n");
    }
}

bool isDiagonal(line_t curline)
{
    uint32_t xmin = min(curline.x1, curline.x2);
    uint32_t xmax = max(curline.x1, curline.x2);
    uint32_t ymin = min(curline.y1, curline.y2);
    uint32_t ymax = max(curline.y1, curline.y2);

    return (xmax - xmin == ymax - ymin);
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
