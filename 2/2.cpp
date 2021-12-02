// 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAXLEN 200
#define MAXLINE 5000

int main()
{
    /*double forward[MAXLINE] = { 0 };
    uint32_t forward_num = 0;
    double down[MAXLINE] = { 0 };
    uint32_t down_num = 0;
    double up[MAXLINE] = { 0 };
    uint32_t up_num = 0;*/

    double hori = 0;
    double depth = 0;
    double res = 0;
    double aim = 0;

    while (1)
    {
        string line;
        char dir[MAXLEN] = { 0 };

        uint32_t num = 0;
        getline(cin, line);

        if (line.length())
        {
            sscanf(line.c_str(), "%s %d", dir, &num);

            string dir_s = dir;

            if (dir_s == "forward")
            {
                hori += num;
                depth += aim * num;
                /*forward[forward_num] = num;
                forward_num++;*/
            }
            else if (dir_s == "down")
            {
                aim += num;
                /*down[down_num] = num;
                down_num++;*/
            }
            else if (dir_s == "up")
            {
                aim -= num;
                /*up[up_num] = num;
                up_num++;*/


            }

        }
        else
        {
            break;
        }
    }

    /*double hori = 0;
    double depth = 0;
    double res = 0;
    for (uint32_t i = 0;i < forward_num;i++)
    {
        hori += forward[i];
    }

    for (uint32_t i = 0;i < down_num;i++)
    {
        depth += down[i];
    }

    for (uint32_t i = 0;i < up_num;i++)
    {
        depth -= up[i];
    }
    */
    res = hori * depth;

    printf("%f", res);

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
