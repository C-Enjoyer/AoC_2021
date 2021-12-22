// 22.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define IN_MAX 900

typedef struct in
{
    int64_t x[2];
    int64_t y[2];
    int64_t z[2];

    bool on;
}in_t;

vector<int> xs, ys, zs;

bool cube[IN_MAX][IN_MAX][IN_MAX] = { 0 };

bool overlap(int64_t cor0s, int64_t cor0e, int64_t cor1s, int64_t cor1e);

in_t lines[IN_MAX] = { 0 };
uint32_t lines_num = 0;


int64_t xmin = INT64_MAX, xmax = INT64_MIN, ymin = INT64_MAX, ymax = INT64_MIN, zmin = INT64_MAX, zmax = INT64_MIN;

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
                        lines[lines_num].x[0] = atoi(lineIn.substr(start, i - start).c_str());
                        num++;
                        xmin = min(xmin, lines[lines_num].x[0]);
                        xs.push_back(lines[lines_num].x[0]);
                    }
                    else if (num == 1)
                    {
                        start = i + 1;
                    }
                    else if (num == 2)
                    {
                        lines[lines_num].y[0] = atoi(lineIn.substr(start, i - start).c_str());
                        num++;
                        ymin = min(ymin, lines[lines_num].y[0]);
                        ys.push_back(lines[lines_num].y[0]);
                    }
                    else if(num == 3)
                    {
                        start = i + 1;
                    }
                    else if (num == 4)
                    {
                        lines[lines_num].z[0] = atoi(lineIn.substr(start, i - start).c_str());
                        num++;
                        zmin = min(zmin, lines[lines_num].z[0]);
                        zs.push_back(lines[lines_num].z[0]);
                    }
                    else if (num == 5)
                    {
                        start = i + 1;
                    }
                }
                else if (lineIn.c_str()[i] == ',')
                {
                    if (num == 1)
                    {
                        lines[lines_num].x[1] = atoi(lineIn.substr(start, i - start).c_str());
                        num++;
                        xmax = max(xmax, lines[lines_num].x[1]);
                        xs.push_back(lines[lines_num].x[1]+1);
                    }
                    else if (num == 3)
                    {
                        lines[lines_num].y[1] = atoi(lineIn.substr(start, i - start).c_str());
                        num++;
                        ymax = max(ymax, lines[lines_num].y[1]);
                        ys.push_back(lines[lines_num].y[1]+1);
                    }
                }
                else if (lineIn.c_str()[i] == 'n')
                {
                    lines[lines_num].on = true;
                }
            }
            lines[lines_num].z[1] = atoi(lineIn.substr(start).c_str());
            zmax = max(zmax, lines[lines_num].z[1]);
            zs.push_back(lines[lines_num].z[1]+1);
            lines_num++;
            
        }
        else
        {
            break;
        }
    }



    //part 1:
    /*uint64_t result = 0;

    for (int x = -50; x <= 50; x++)
    {
        for (int y = -50; y <= 50; y++)
        {
            for (int z = -50; z <= 50; z++)
            {
                bool on = false;
                for (uint32_t i = 0;i < lines_num; i++)
                {
                    if (lines[i].x[0] <= x && x <= lines[i].x[1] &&
                        lines[i].y[0] <= y && y <= lines[i].y[1] &&
                        lines[i].z[0] <= z && z <= lines[i].z[1])
                    {
                        on = lines[i].on;
                    }
                }
                if (on)
                {
                    result++;
                }
            }
        }
    }

    printf("%llu", result);*/

    //part2:

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    sort(zs.begin(), zs.end());

    for (uint32_t i=0;i<lines_num;i++)
    {
        int64_t xnew[2] = { lower_bound(xs.begin(), xs.end(), lines[i].x[0]) - xs.begin(), lower_bound(xs.begin(), xs.end(), lines[i].x[1] + 1) - xs.begin() };
        int64_t ynew[2] = { lower_bound(ys.begin(), ys.end(), lines[i].y[0]) - ys.begin(), lower_bound(ys.begin(), ys.end(), lines[i].y[1] + 1) - ys.begin() };
        int64_t znew[2] = { lower_bound(zs.begin(), zs.end(), lines[i].z[0]) - zs.begin(), lower_bound(zs.begin(), zs.end(), lines[i].z[1] + 1) - zs.begin() };
        
        for (int64_t x = xnew[0]; x < xnew[1]; x++)
        {
            for (int64_t y = ynew[0]; y < ynew[1]; y++)
            {
                for (int64_t z = znew[0]; z < znew[1]; z++)
                {
                    cube[x][y][z] = lines[i].on;
                }
            }
        }
    }

    uint64_t result = 0;

    for (int x = 0; x < xs.size() - 1; x++)
    {
        for (int y = 0; y < ys.size() - 1; y++)
        {
            for (int z = 0; z < zs.size() - 1; z++)
            {
                if (cube[x][y][z])
                {
                    result += ((uint64_t)(xs[x + 1] - xs[x])) * ((uint64_t)(ys[y + 1] - ys[y])) * ((uint64_t)(zs[z + 1] - zs[z]));
                }
            }
        }
    }
    
    printf("%llu", result);
}

bool overlap(int64_t cor0s, int64_t cor0e, int64_t cor1s, int64_t cor1e)
{
    if (cor0s <= cor1s <= cor0e)
    {
        return true;
    }
    if (cor0s <= cor1e <= cor0e)
    {
        return true;
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
