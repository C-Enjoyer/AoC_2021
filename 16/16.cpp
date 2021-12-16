// 16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_NUMS 100

uint32_t getNum(string s);
void handlePacket(string s, uint32_t from, uint32_t to);
uint32_t handlePackets(string s, uint32_t from, uint32_t num);
uint32_t handleLit(string s, uint32_t from);
uint32_t handleOp(string s, uint32_t from);
void convertToBinString(void);
uint32_t get4Padded(uint32_t num);

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
    handlePacket(bin, 0, bin.length());

    printf("Result: %llu", sum);
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

void handlePacket(string s, uint32_t from, uint32_t to)
{
    uint32_t start = from;
    while (1)
    {
        uint32_t version = getNum(s.substr(start, 3));
        uint32_t typeID = getNum(s.substr(start+3, 3));

        sum += version;
        start += 6;

        if (typeID == 4)
        {
            start = handleLit(s, start);
        }
        else
        {
            start = handleOp(s, start);
        }

        start = (get4Padded(start - 1) + 1);

        if (start >= to || start >= s.length())
        {
            break;
        }
    }
}

uint32_t handlePackets(string s, uint32_t from, uint32_t num)
{
    uint32_t pos = from;
    for (uint32_t i = 0;i < num;i++)
    {
        uint32_t version = getNum(s.substr(pos, 3));
        uint32_t typeID = getNum(s.substr(pos + 3, 3));

        sum += version;

        if (typeID == 4)
        {
            pos = handleLit(s, pos + 6);
        }
        else
        {
            pos = handleOp(s, pos + 6);
        }
    }
    return pos;
}

uint32_t handleLit(string s, uint32_t from)
{
    uint32_t pos = from;
    uint16_t nums[MAX_NUMS] = { 0 };
    uint32_t nums_num = 0;
    while (1)
    {
        uint32_t pre = getNum(s.substr(pos, 1));

        if (pre == 1)
        {
            nums[nums_num] = getNum(s.substr(pos + 1, 4));
            nums_num++;
            pos += 5;
        }
        else
        {
            nums[nums_num] = getNum(s.substr(pos + 1, 4));
            nums_num++;
            pos += 5;
            break;
        }
    }

    return (get4Padded(pos-1) + 1);
}

uint32_t handleOp(string s, uint32_t from)
{
    uint32_t pos = from;
    uint32_t lenghtTypeID = getNum(s.substr(pos, 1));
    if (lenghtTypeID == 0)
    {
        uint32_t length = getNum(s.substr(pos+1, 15));
        handlePacket(s, pos+16, pos + 16 + length);
        return (get4Padded(pos + length + 1 + 15 - 1) + 1);
    }
    else
    {
        uint32_t subPackets = getNum(s.substr(pos + 1, 11));
        return (get4Padded((handlePackets(s, pos + 12, subPackets) + 1 + 11 - 1)) + 1);
    }
}

uint32_t get4Padded(uint32_t num)
{
    uint8_t mod4 = num % 4;

    if (mod4 == 0)
    {
        return num;
    }
    else
    {
        return (num + (4 - (mod4)));
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
