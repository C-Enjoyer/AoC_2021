// 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#define MAXLINE 50000
#define LEN 12

using namespace std;

bool getMostBit(uint32_t pos, bool isOx);
uint32_t elimWithoutBit(bool bit, uint32_t pos, bool isOx);
uint32_t getLeft(bool isOx);
void printLeft(bool isOx);

bool bin_array[MAXLINE][LEN];
bool array_ox[MAXLINE] = { false };
bool array_co2[MAXLINE] = { false };
uint32_t ox_ok = 0;
uint32_t co2_ok = 0;
uint32_t array_num = 0;

int main()
{

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
                    bin_array[array_num][i] = false;
                }
                else
                {
                    bin_array[array_num][i] = true;
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
    /*
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
            gamma |= (1 << (LEN - 1-i));
        }
        else if (one == zero)
        {
            auto x = 0;
        }
        else
        {
            eps |= (1 << (LEN - 1 - i));
        }
    }*/


    

    /*double result = gamma * eps;
    auto x = 0;*/

    for(uint32_t j = 0;j < array_num;j++)
    {
        array_ox[j] = true;
        array_co2[j] = true;
    }

    ox_ok = array_num;
    co2_ok = array_num;

    uint32_t ox = 0;
    uint32_t co2 = 0;

    for (uint32_t i = 0;i < LEN;i++)
    {
        bool mostBit = getMostBit(i, true);
        uint32_t left = elimWithoutBit(mostBit, i, true);

        printf("left = %d\n",left);
        printLeft(true);
        printf("\n");
        if (left == 1)
        {
            ox = getLeft(true);
            break;
        }
    }

    for (uint32_t i = 0;i < LEN;i++)
    {
        bool leastBit = !getMostBit(i, false);
        uint32_t left = elimWithoutBit(leastBit, i, false);

        /*printf("left = %d\n",left);
        printLeft(false);
        printf("\n");*/
        if (left == 1)
        {
            co2 = getLeft(false);
            break;
        }
    }

    double result = ox * co2;

    printf("Result = %f", result);








}

bool getMostBit(uint32_t pos, bool isOx)
{
    uint32_t one = 0, zero = 0;
    for (uint32_t j = 0;j < array_num;j++)
    {
        if ((isOx && array_ox[j]) || (!isOx && array_co2[j]))
        {
            if (bin_array[j][pos])
            {
                one++;
            }
            else
            {
                zero++;
            }
        }
    }
    return (one >= zero);
}

uint32_t elimWithoutBit(bool bit, uint32_t pos, bool isOx)
{
    for (uint32_t j = 0;j < array_num;j++)
    {
        if (bin_array[j][pos] != bit)
        {
            if (isOx && array_ox[j])
            {
                array_ox[j] = false;
                ox_ok--;
            }
            else if(!isOx && array_co2[j])
            {
                array_co2[j] = false;
                co2_ok--;
            }
        }
    }

    return (isOx) ? (ox_ok) : (co2_ok);
}

uint32_t getLeft(bool isOx)
{
    for (uint32_t j = 0;j < array_num;j++)
    {
        if ((isOx && array_ox[j]) || (!isOx && array_co2[j]))
        {
            uint32_t retval = 0;
            for (uint32_t i = 0;i < LEN;i++)
            {
                if (bin_array[j][i])
                {
                    retval |= (1 << (LEN - 1 - i));
                }
            }
            return retval;
        }
    }
    return 0;
}

void printLeft(bool isOx)
{
    for (uint32_t j = 0;j < array_num;j++)
    {
        if ((isOx && array_ox[j]) || (!isOx && array_co2[j]))
        {
            printf("BIN: ");
            for (uint32_t i = 0;i < LEN;i++)
            {
                if (bin_array[j][i])
                {
                    printf("1");
                }
                else
                {
                    printf("0");
                }
            }
            printf("\n");
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
