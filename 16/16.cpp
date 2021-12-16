// 16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_NUMS 20
#define ID_NONE 255
#define MAX_RES 500

uint32_t getNum(string s);
double handleResult(double* res, uint32_t res_num, uint32_t id);
double handlePacket(string s, uint32_t* from, uint32_t to, uint32_t id);
double handlePackets(string s, uint32_t* from, uint32_t num, uint32_t id);
double handleLit(string s, uint32_t* from);
double handleOp(string s, uint32_t* from, uint32_t id);
void convertToBinString(void);

string in;
string bin;

uint64_t sum = 0;


int main()
{
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            in = lineIn;
        }
        else
        {
            break;
        }
    }

    
    convertToBinString();
    uint32_t from = 0;
    double result = handlePacket(bin, &from, bin.length(), ID_NONE);

    //part1:
    printf("Result: %llu\n", sum);
    //part2:
    printf("Result: %f\n", result);
}

void convertToBinString(void)
{
    for (uint32_t i = 0;i < in.length();i++)
    {
        switch (in.c_str()[i])
        {
            case '0': bin.append("0000");
                break;
            case '1': bin.append("0001");
                break;
            case '2': bin.append("0010");
                break;
            case '3': bin.append("0011");
                break;
            case '4': bin.append("0100");
                break;
            case '5': bin.append("0101");
                break;
            case '6': bin.append("0110");
                break;
            case '7': bin.append("0111");
                break;
            case '8': bin.append("1000");
                break;
            case '9': bin.append("1001");
                break;
            case 'A': bin.append("1010");
                break;
            case 'B': bin.append("1011");
                break;
            case 'C': bin.append("1100");
                break;
            case 'D': bin.append("1101");
                break;
            case 'E': bin.append("1110");
                break;
            case 'F': bin.append("1111");
                break;
        }
    }
}

uint32_t getNum(string s)
{
    return stoi(s, 0, 2);
}

double handleResult(double* res, uint32_t res_num, uint32_t id)
{
    if (id == ID_NONE)
    {
        return res[0];
    }
    if (id == 0)
    {
        double sum = 0;
        for (uint32_t i = 0;i < res_num;i++)
        {
            sum += res[i];
        }
        return sum;
    }
    if (id == 1)
    {
        double prod = 1;
        for (uint32_t i = 0;i < res_num;i++)
        {
            prod *= res[i];
        }
        return prod;
    }
    if (id == 2)
    {
        double minVal = DBL_MAX;
        for (uint32_t i = 0;i < res_num;i++)
        {
            minVal = min(minVal, res[i]);
        }
        return minVal;
    }
    if (id == 3)
    {
        double maxVal = DBL_MIN;
        for (uint32_t i = 0;i < res_num;i++)
        {
            maxVal = max(maxVal, res[i]);
        }
        return maxVal;
    }
    if (id == 5)
    {
        if (res[0] > res[1])
        {
            return 1;
        }
        return 0;
    }
    if (id == 6)
    {
        if (res[0] < res[1])
        {
            return 1;
        }
        return 0;
    }
    if (id == 7)
    {
        if (res[0] == res[1])
        {
            return 1;
        }
        return 0;
    }
    return 0;
}

double handlePacket(string s, uint32_t* from, uint32_t to, uint32_t id)
{
    double res[MAX_RES] = { 0 };
    uint32_t res_num = 0;
    printf("Packet0 from %lu\n", *from);
    while (1)
    {
        bool packetLeft = false;
        for (uint32_t i = *from; i < s.length(); i++)
        {
            if (s.c_str()[i] == '1')
            {
                packetLeft = true;
                break;
            }
        }

        if (!packetLeft)
        {
            break;
        }

        uint32_t version = getNum(s.substr(*from, 3));
        *from += 3;
        uint32_t typeID = getNum(s.substr(*from, 3));
        *from += 3;

        printf("Packet0 with version: %lu\n", version);

        sum += version;
        

        if (typeID == 4)
        {
            res[res_num] = handleLit(s, from);
            res_num++;
        }
        else
        {
            res[res_num] = handleOp(s, from, typeID);
            res_num++;
        }

        if (*from >= to || *from >= s.length())
        {
            break;
        }
    }
    

    return handleResult(res, res_num, id);
}

double handlePackets(string s, uint32_t* from, uint32_t num, uint32_t id)
{
    double res[MAX_RES] = { 0 };
    uint32_t res_num = 0;

    for (uint32_t i = 0;i < num;i++)
    {
        uint32_t version = getNum(s.substr(*from, 3));
        *from += 3;
        uint32_t typeID = getNum(s.substr(*from, 3));
        *from += 3;

        printf("Packet1 with version: %lu\n", version);

        sum += version;

        if (typeID == 4)
        {
            res[res_num] = handleLit(s, from);
            res_num++;
        }
        else
        {
            res[res_num] = handleOp(s, from, typeID);
            res_num++;
        }
    }
    return handleResult(res, res_num, id);
}

double handleLit(string s, uint32_t* from)
{
    double result = 0;
    uint16_t nums[MAX_NUMS] = { 0 };
    uint32_t nums_num = 0;

    while (1)
    {
        uint32_t pre = getNum(s.substr(*from, 1));
        *from += 1;

        if (pre == 1)
        {
            nums[nums_num] = getNum(s.substr(*from, 4));
            nums_num++;
            *from += 4;
        }
        else
        {
            nums[nums_num] = getNum(s.substr(*from, 4));
            nums_num++;
            *from += 4;
            break;
        }
    }

    uint64_t number = 0;

    for (int i = 0;i < nums_num; i++)
    {
        for (uint8_t j = 0;j < 4;j++)
        {
            if (nums[i] & (1 << j))
            {
                uint32_t shift = (4 * ((nums_num - 1) - i) + j);
                number |= (1ULL << shift);
            }
        }
    }

    printf("Lit with %llu\n", number);

    return (double) number;
}

double handleOp(string s, uint32_t* from, uint32_t id)
{
    uint32_t lenghtTypeID = getNum(s.substr(*from, 1));
    *from += 1;
    if (lenghtTypeID == 0)
    {
        uint32_t length = getNum(s.substr(*from, 15));
        *from += 15;
        printf("Op with length: %lu\n", length);
        if (length >= s.length())
        {
            auto x = 0;
        }
        return handlePacket(s, from, *from + length, id);
    }
    else
    {
        uint32_t subPackets = getNum(s.substr(*from, 11));
        *from += 11;
        printf("Op with subPackets: %lu\n", subPackets);
        return handlePackets(s, from, subPackets, id);
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
