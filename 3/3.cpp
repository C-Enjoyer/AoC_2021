// 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#define MAXLINE 50000
#define LEN 5

using namespace std;

int main()
{
    bool array[MAXLINE][LEN];
    bool array_ox[MAXLINE] = { true };
   uint32_t array_num = 0;
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            //sscanf(line.c_str(), "%s %d", dir, &num);
            for (uint32_t i = 0;i < LEN;i++)
            {
                if (line[i] == '0')
                {
                    array[array_num][i] = false;
                }
                else
                {
                    array[array_num][i] = true;
                }
                
            }
            array_num++;
        }
        else
        {
            break;
        }
    }
    
    /*uint32_t gamma = 0;
    uint32_t eps = 0;*/
    bool res[LEN] = { false };

    for (uint32_t i = 0;i < LEN;i++)
    {
        uint32_t one = 0;
        uint32_t zero = 0;
        for (uint32_t j = 0;j < array_num;j++)
        {
            if (array[j][i])
            {
                one++;
            }
            else
            {
                zero++;
            }
        }

        if (one > zero)
        {
            res[LEN - 1 - i] = true;
        }

        /*if (one > zero)
        {
            gamma |= (1 << (LEN - 1-i));
        }
        else if (one == zero)
        {
            auto x = 0;
        }
        else
        {
            eps |= (1 << (LEN - 1 - i));
        }*/
    }
    

    /*double result = gamma * eps;
    auto x = 0;*/

    uint32_t ox_ok = array_num;

    for (uint32_t i = 0;i < LEN;i++)
    {
        for (uint32_t j = 0;j < array_num;j++)
        {
            if(array[j][i] != res[i])
            {
                array_ox[j] = false;
                ox_ok--;
                if (ox_ok == 0)
                {
                    auto x = 0;
                }
            }
        }
        auto x = 0;
    }

    auto x = 0;








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
