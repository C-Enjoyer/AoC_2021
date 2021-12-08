// 8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define MAX_LINES     3000
#define LINE_IN     10
#define LINE_OUT    4
#define MISSING_SEGMENTS_069 (3)
#define MISSING_SEGMENTS_235 (4)

using namespace std;

typedef enum segment
{
    A = 0,
    B,
    C,
    D,
    E,
    F,
    G,
    SEG_MAX
}segment_t;

#define POS_MAX     SEG_MAX

typedef struct line
{
    bool input[LINE_IN][SEG_MAX];
    bool output[LINE_OUT][SEG_MAX];
    bool pos[POS_MAX][SEG_MAX];

    int32_t pos069[MISSING_SEGMENTS_069];
    int32_t pos069_num;

    int32_t pos235[MISSING_SEGMENTS_235];
    int32_t pos235_num;
}line_t;

/*pos:

 0000
1    5
1    5 
 6666
2    4
2    4
 3333
 */
void stringToStruct(string s, uint32_t line_num, uint32_t digit_num, bool In);
uint32_t getSegmentNumFromDigit(uint32_t line_num, uint32_t digit_num, bool In);
void checkPossibilities(uint32_t line_num, uint32_t digit_num, bool In);
void clearImpossible(uint32_t line_num, uint32_t* posPossible, uint32_t posPossibleNum, uint32_t* segmentPossible, uint32_t segmentPossibleNum);
void getSegmentsFromDigit(uint32_t line_num, uint32_t digit_num, bool In, uint32_t* segmentPossbile, uint32_t* segmentPossbileNum);
bool isLineSolved(uint32_t line_num);
void getMissingSegments(uint32_t line_num, uint32_t digit_num, bool In, uint32_t* missingSegments);
uint64_t getOutputFromLine(uint32_t line_num);
uint8_t getValueFromOutDigit(uint32_t line_num, uint32_t digit);

line_t lines[MAX_LINES] = { false };
uint32_t lines_num = 0;

int main()
{
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            string cur = "";
            int32_t lastSeperator = -1;
            uint32_t lines_digit_num = 0;
            bool isIn = true;
            for (uint32_t i = 0;i < lineIn.length();i++)
            {
                if (lineIn[i] == ' ')
                {
                    cur = lineIn.substr(lastSeperator + 1, i - (lastSeperator + 1));
                    lastSeperator = i;
                    stringToStruct(cur, lines_num, lines_digit_num, isIn);
                    lines_digit_num++;
                }
                else if (lineIn[i] == '|')
                {
                    i++;
                    lastSeperator = i;
                    isIn = false;
                    lines_digit_num = 0;
                }
                else if (i == lineIn.length() - 1)
                {
                    cur = lineIn.substr(lastSeperator + 1);
                    stringToStruct(cur, lines_num, lines_digit_num, isIn);
                    lines_digit_num++;
                }
            }
            lines_num++;
        }
        else
        {
            break;
        }
    }

    //part 1
    /*
    uint64_t result = 0;
    for (uint32_t curLine = 0; curLine < lines_num; curLine++)
    {
        for (uint32_t digit = 0; digit < LINE_OUT;digit++)
        {
            uint32_t segments = getSegmentNumFromDigit(curLine, digit, false);
            if (segments == 2 || segments == 4 || segments == 3 || segments == 7)
            {
                result++;
            }
        }
    }
    printf("Result: %llu", result);
    */


    //part 2

    //all options are possible
    for (uint32_t curLine = 0; curLine < lines_num; curLine++)
    {
        for (uint32_t pos = 0; pos < POS_MAX;pos++)
        {
            for (uint32_t segment = 0; segment < SEG_MAX;segment++)
            {
                lines[curLine].pos[pos][segment] = true;
            }
        }
        for (uint32_t pos069 = 0; pos069 < MISSING_SEGMENTS_069; pos069++)
        {
            lines[curLine].pos069[pos069] = -1;
        }
        for (uint32_t pos235 = 0; pos235 < MISSING_SEGMENTS_235; pos235++)
        {
            lines[curLine].pos235[pos235] = -1;
        }
    }

    for (uint32_t curLine = 0; curLine < lines_num; curLine++)
    {
        for (uint32_t digit = 0;digit < LINE_IN + LINE_OUT; digit++)
        {
            bool isIn = (digit < LINE_IN);
            uint32_t digit_num = (isIn) ? (digit) : (digit - LINE_IN);

            checkPossibilities(curLine, digit_num, isIn);
        }
    }

    uint32_t solved = 0;

    for (uint32_t curLine = 0; curLine < lines_num; curLine++)
    {
        uint32_t posPossible[] = { 2, 5, 6 };
        uint32_t posPossibleNum = sizeof(posPossible) / sizeof(posPossible[0]);

        clearImpossible(curLine, posPossible, posPossibleNum, (uint32_t*)lines[curLine].pos069, (uint32_t)lines[curLine].pos069_num);

        if (isLineSolved(curLine))
        {
            solved++;
        }
    }

    uint64_t result = 0;

    for (uint32_t curLine = 0; curLine < lines_num; curLine++)
    {
        result += getOutputFromLine(curLine);
    }

    printf("Result: %llu", result);

}

uint64_t getOutputFromLine(uint32_t line_num)
{
    uint64_t result = 0;
    for (uint32_t digit = 0; digit < LINE_OUT; digit++)
    {
        uint8_t digitValue = getValueFromOutDigit(line_num, digit);

        result += digitValue * pow(10, LINE_OUT - 1 - digit);
    }

    return result;
}

uint8_t getValueFromOutDigit(uint32_t line_num, uint32_t digit)
{
    uint8_t crypt = 0;

    for (uint32_t seg = 0; seg < SEG_MAX; seg++)
    {
        if (lines[line_num].output[digit][seg]) // segment in digit
        {
            for (uint32_t pos = 0; pos < POS_MAX;pos++)
            {
                if (lines[line_num].pos[pos][seg])
                {
                    crypt |= (1 << pos);
                    break;
                }
            }
        }
    }
   
    switch (crypt)
    {
        case 0b00111111: return 0;
        case 0b00110000: return 1;
        case 0b01101101: return 2;
        case 0b01111001: return 3;
        case 0b01110010: return 4;
        case 0b01011011: return 5;
        case 0b01011111: return 6;
        case 0b00110001: return 7;
        case 0b01111111: return 8;
        case 0b01111011: return 9;
    }

    return 0;
}


bool isLineSolved(uint32_t line_num)
{
    for (uint32_t pos = 0; pos < POS_MAX;pos++)
    {
        uint32_t segPossible = 0;
        for (uint32_t seg = 0; seg < POS_MAX; seg++)
        {
            if (lines[line_num].pos[pos][seg])
            {
                segPossible++;
            }
        }
        if (segPossible != 1)
        {
            return false;
        }
    }

    return true;
}

void checkPossibilities(uint32_t line_num, uint32_t digit_num, bool In)
{
    uint32_t segmentNum = getSegmentNumFromDigit(line_num, digit_num, In);

    if (segmentNum == 2) //digit 1
    {
        uint32_t posPossible[] = { 4 , 5 };
        uint32_t segmentPossible[SEG_MAX] = { 0 };
        uint32_t segmentPossibleNum = 0;
        uint32_t posPossibleNum = sizeof(posPossible) / sizeof(posPossible[0]);

        getSegmentsFromDigit(line_num, digit_num, In, segmentPossible, &segmentPossibleNum);
        clearImpossible(line_num, posPossible, posPossibleNum, segmentPossible, segmentPossibleNum);
    }
    else if (segmentNum == 3) // digit 7
    {
        uint32_t posPossible[] = { 0, 4 , 5 };
        uint32_t segmentPossible[SEG_MAX] = { 0 };
        uint32_t segmentPossibleNum = 0;
        uint32_t posPossibleNum = sizeof(posPossible) / sizeof(posPossible[0]);

        getSegmentsFromDigit(line_num, digit_num, In, segmentPossible, &segmentPossibleNum);
        clearImpossible(line_num, posPossible, posPossibleNum, segmentPossible, segmentPossibleNum);
    }
    else if (segmentNum == 4) // digit 4
    {
        uint32_t posPossible[] = {1 , 4, 5, 6};
        uint32_t segmentPossible[SEG_MAX] = { 0 };
        uint32_t segmentPossibleNum = 0;
        uint32_t posPossibleNum = sizeof(posPossible) / sizeof(posPossible[0]);

        getSegmentsFromDigit(line_num, digit_num, In, segmentPossible, &segmentPossibleNum);
        clearImpossible(line_num, posPossible, posPossibleNum, segmentPossible, segmentPossibleNum);
    }

    else if (segmentNum == 6) // digit 0,6
    {
        uint32_t missingSegments[SEG_MAX] = { 0 };

        getMissingSegments(line_num, digit_num, In, missingSegments);

        if (find(lines[line_num].pos069, lines[line_num].pos069 + MISSING_SEGMENTS_069, missingSegments[0]) == lines[line_num].pos069 + MISSING_SEGMENTS_069)
        {
            lines[line_num].pos069[lines[line_num].pos069_num] = missingSegments[0];
            lines[line_num].pos069_num++;
        }
    }
    else if (segmentNum == 5) // digit 2,3,5
    {
        uint32_t missingSegments[SEG_MAX] = { 0 };

        getMissingSegments(line_num, digit_num, In, missingSegments);

        if (find(lines[line_num].pos235, lines[line_num].pos235 + MISSING_SEGMENTS_235, missingSegments[0]) == lines[line_num].pos235 + MISSING_SEGMENTS_235)
        {
            lines[line_num].pos235[lines[line_num].pos235_num] = missingSegments[0];
            lines[line_num].pos235_num++;
        }

        if (find(lines[line_num].pos235, lines[line_num].pos235 + MISSING_SEGMENTS_235, missingSegments[1]) == lines[line_num].pos235 + MISSING_SEGMENTS_235)
        {
            lines[line_num].pos235[lines[line_num].pos235_num] = missingSegments[1];
            lines[line_num].pos235_num++;
        }
    }
}

void getMissingSegments(uint32_t line_num, uint32_t digit_num, bool In, uint32_t* missingSegments)
{
    uint32_t missingSegmentsNum = 0;
    for (uint32_t i = 0;i < SEG_MAX;i++)
    {
        if (In)
        {
            if (!lines[line_num].input[digit_num][i])
            {
                missingSegments[missingSegmentsNum] = i;
                missingSegmentsNum++;
            }
        }
        else
        {
            if (!lines[line_num].output[digit_num][i])
            {
                missingSegments[missingSegmentsNum] = i;
                missingSegmentsNum++;
            }
        }
    }
}

void getSegmentsFromDigit(uint32_t line_num, uint32_t digit_num, bool In, uint32_t* segmentPossbile, uint32_t* segmentPossbileNum)
{
    for (uint32_t i = 0;i < SEG_MAX;i++)
    {
        if (In)
        {
            if (lines[line_num].input[digit_num][i])
            {
                segmentPossbile[*segmentPossbileNum] = i;
                (*segmentPossbileNum)++;
            }
        }
        else
        {
            if (lines[line_num].output[digit_num][i])
            {
                segmentPossbile[*segmentPossbileNum] = i;
                (*segmentPossbileNum)++;
            }
        }
    }
}

void clearImpossible(uint32_t line_num, uint32_t* posPossible, uint32_t posPossibleNum, uint32_t* segmentPossible, uint32_t segmentPossibleNum)
{
    for (uint32_t pos = 0;pos < POS_MAX;pos++)
    {
        if (find(posPossible, posPossible + posPossibleNum, pos) != posPossible + posPossibleNum) // found pos in posPossbile
        {
            for (uint32_t seg = 0;seg < SEG_MAX;seg++)
            {
                if (find(segmentPossible, segmentPossible + segmentPossibleNum, seg) == segmentPossible + segmentPossibleNum) // didn't find seg in segmentPossbile
                {
                    lines[line_num].pos[pos][seg] = false;
                }
            }
        }
        else
        {
            for (uint32_t segmentPossibleCur = 0; segmentPossibleCur < segmentPossibleNum; segmentPossibleCur++) // delete all possible segments from current segment
            {
                lines[line_num].pos[pos][segmentPossible[segmentPossibleCur]] = false;
            }
        }
    }
}

uint32_t getSegmentNumFromDigit(uint32_t line_num, uint32_t digit_num, bool In)
{
    uint32_t segments = 0;
    for (uint32_t segment = 0; segment < SEG_MAX;segment++)
    {
        if (In)
        {
            if (lines[line_num].input[digit_num][segment])
            {
                segments++;
            }
        }
        else
        {
            if (lines[line_num].output[digit_num][segment])
            {
                segments++;
            }
        }

    }

    return segments;
}

void stringToStruct(string s, uint32_t line_num, uint32_t digit_num, bool In)
{
    if (s.find('a') != std::string::npos)
    {
        if (In) lines[line_num].input[digit_num][A] = true;
        else    lines[line_num].output[digit_num][A] = true;
    }
    if (s.find('b') != std::string::npos)
    {
        if (In) lines[line_num].input[digit_num][B] = true;
        else    lines[line_num].output[digit_num][B] = true;
    }
    if (s.find('c') != std::string::npos)
    {
        if (In) lines[line_num].input[digit_num][C] = true;
        else    lines[line_num].output[digit_num][C] = true;
    }
    if (s.find('d') != std::string::npos)
    {
        if (In) lines[line_num].input[digit_num][D] = true;
        else    lines[line_num].output[digit_num][D] = true;
    }
    if (s.find('e') != std::string::npos)
    {
        if (In) lines[line_num].input[digit_num][E] = true;
        else    lines[line_num].output[digit_num][E] = true;
    }
    if (s.find('f') != std::string::npos)
    {
        if (In) lines[line_num].input[digit_num][F] = true;
        else    lines[line_num].output[digit_num][F] = true;
    }
    if (s.find('g') != std::string::npos)
    {
        if (In) lines[line_num].input[digit_num][G] = true;
        else    lines[line_num].output[digit_num][G] = true;
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
