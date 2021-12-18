// 18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define NUM_MAX 20000
#define NONE (-1)

typedef enum side
{
    LEFT = 0,
    RIGHT = 1,
    SIDES
}side_t;

typedef struct num
{
    bool existent;
    int hid;
    int lid[SIDES];
    int l, r;
    uint32_t row;
}num_t;

void parseLine(string* s);
uint32_t parsePair(string* s, uint32_t startpos, uint32_t len);
void addRows(uint32_t row0, uint32_t row1);
uint32_t getRowMaster(uint32_t row);
void reduceRow(uint32_t row);
void printRow(string* s, uint32_t row);
void printNum(string* s, uint32_t num);
int getbelow4Layer(uint32_t* layer, uint32_t num);
void explode(uint32_t num, uint32_t expval, side_t si);
void explode(uint32_t num);
uint32_t findLeftMost(uint32_t num);
uint32_t findRightMost(uint32_t num);
void split(uint32_t num);
int getHigher9(uint32_t num);
uint64_t getMagnitude(uint32_t num);

num_t nums[NUM_MAX] = { 0 };
uint32_t nums_num = 0;
uint32_t rows = 0;

int main()
{
    for (uint32_t i = 0;i < NUM_MAX;i++)
    {
        nums[i].existent = false;
        nums[i].hid = NONE;
        nums[i].lid[LEFT] = NONE;
        nums[i].lid[RIGHT] = NONE;
        nums[i].l = NONE;
        nums[i].r = NONE;
    }

    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length())
        {
            parseLine(&lineIn);
            rows++;
        }
        else
        {
            break;
        }
    }

    string s;
    for (uint32_t i = 1;i < rows;i++)
    {
        addRows(0, i);
        printRow(&s, 0);
        printf("%s\n", s.c_str());
        s.clear();

        reduceRow(0);
        printRow(&s, 0);
        printf("%s\n", s.c_str());
        s.clear();
    }

    uint32_t master = getRowMaster(0);
    uint64_t result = getMagnitude(master);

    printf("%llu", result);
}

uint64_t getMagnitude(uint32_t num)
{
    uint64_t result = 0;
    if (nums[num].l != NONE)
    {
        result += nums[num].l * 3;
    }
    else
    {
        result += getMagnitude(nums[num].lid[LEFT]) * 3;
    }

    if (nums[num].r != NONE)
    {
        result += nums[num].r * 2;
    }
    else
    {
        result += getMagnitude(nums[num].lid[RIGHT]) * 2;
    }

    return result;
}

void reduceRow(uint32_t row)
{
    while (1)
    {
        uint32_t master = getRowMaster(row);
        uint32_t layer = 0;
        int result = getbelow4Layer(&layer, master);
        string s;

        if (result != NONE)
        {
            explode(result);
        }
        else
        {
            result = getHigher9(master);
            if (result != NONE)
            {
                split(result);
            }
            else
            {
                break;
            }
        }

        //printRow(&s, 0);
        //printf("%s\n", s.c_str());
    }
}

void split(uint32_t num)
{
    side_t s = (nums[num].l > 9) ? (LEFT) : (RIGHT);
    uint32_t numToSplit = 0;
    uint32_t l = 0, r = 0;;

    if (s == LEFT)
    {
        numToSplit = nums[num].l;
        nums[num].l = NONE;
    }
    else
    {
        numToSplit = nums[num].r;
        nums[num].r = NONE;
    }

    r = (numToSplit / 2) + (numToSplit % 2);
    l = numToSplit - r;
    

    nums[num].lid[s] = nums_num;
    nums[nums_num].existent = true;
    nums[nums_num].hid = num;
    nums[nums_num].l = l;
    nums[nums_num].r = r;
    nums[nums_num].row = nums[num].row;
    nums[nums_num].lid[LEFT] = NONE;
    nums[nums_num].lid[RIGHT] = NONE;
    nums_num++;
}

int getHigher9(uint32_t num)
{
    if (nums[num].l > 9)
    {
        return num;
    }
    else if (nums[num].l == NONE)
    {
        int res = getHigher9(nums[num].lid[LEFT]);
        if (res != -1) return res;
    }
   
    if (nums[num].r > 9)
    {
        return num;
    }
    else if (nums[num].r == NONE)
    {
        int res = getHigher9(nums[num].lid[RIGHT]);
        if (res != -1) return res;
    }

    return -1;
}

void explode(uint32_t num)
{
    explode(num, nums[num].l, LEFT);
    explode(num, nums[num].r, RIGHT);
    nums[num].existent = false;

    if (nums[nums[num].hid].lid[LEFT] == num)
    {
        nums[nums[num].hid].lid[LEFT] = NONE;
        nums[nums[num].hid].l = 0;
    }
    else if (nums[nums[num].hid].lid[RIGHT] == num)
    {
        nums[nums[num].hid].lid[RIGHT] = NONE;
        nums[nums[num].hid].r = 0;
    }
}

void explode(uint32_t num, uint32_t expval, side_t si)
{
    int upper = nums[num].hid;

    if (upper == NONE)
    {
        return;
    }

    if (si == LEFT)
    {
        if (nums[upper].lid[RIGHT] == num) //[1,[3,4]] or [[1,2],[3,4]] => [3,4] explodes
        {
            if (nums[upper].l != NONE) //[1, [3, 4]]
            {
                nums[upper].l += expval;
            }
            else //[[1, 2], [3, 4]]
            {
                //explode(nums[upper].lid[LEFT], expval, si);
                nums[findRightMost(nums[upper].lid[LEFT])].r += expval;
            }
        }
        else //[[1,2],4] or [[1,2]] or [[1,2],[3,4]] => [1,2] explodes
        {
            explode(upper, expval, si);
        }
    }
    else if(si == RIGHT)
    {
        if (nums[upper].lid[LEFT] == num) //[[1,2],4] or [[1,2],[3,4]] => [1,2] explodes
        {
            if (nums[upper].r != NONE) //[[1,2],4]
            {
                nums[upper].r += expval;
            }
            else //[[1, 2], [3, 4]]
            {
                nums[findLeftMost(nums[upper].lid[RIGHT])].l += expval;
            }
        }
        else //[1,[3,4]] or [[3,4]] or [[1,2], [3, 4]] => [3,4] explodes
        {
            explode(upper, expval, si);
        }
    }
}

uint32_t findLeftMost(uint32_t num)
{
    if (nums[num].l != NONE)
    {
        return num;
    }
    
    return findLeftMost(nums[num].lid[LEFT]);
}

uint32_t findRightMost(uint32_t num)
{
    if (nums[num].r != NONE)
    {
        return num;
    }

    return findRightMost(nums[num].lid[RIGHT]);
}

int getbelow4Layer(uint32_t* layer, uint32_t num)
{
    if (nums[num].lid[LEFT] != NONE)
    {
        if (*layer >= 4 - 1)
        {
            return nums[num].lid[LEFT];
        }
        else
        {
            (*layer)++;
            int res = getbelow4Layer(layer, nums[num].lid[LEFT]);
            if (res != NONE) return res;
            else (*layer)--;
        }
    }

    if (nums[num].lid[RIGHT] != NONE)
    {
        if (*layer >= 4 - 1)
        {
            return nums[num].lid[RIGHT];
        }
        else
        {
            (*layer)++;
            int res = getbelow4Layer(layer, nums[num].lid[RIGHT]);
            if (res != NONE) return res;
            else (*layer)--;
        }
    }
    return NONE;
}

void printRow(string*s, uint32_t row)
{
    uint32_t master = getRowMaster(row);
    printNum(s, master);
}

void printNum(string *s, uint32_t num)
{
    s->append("[");

    if (nums[num].lid[LEFT] != NONE)
    {
        printNum(s, nums[num].lid[LEFT]);
    }
    else
    {
        s->append(to_string(nums[num].l));
    }

    s->append(",");

    if (nums[num].lid[RIGHT] != NONE)
    {
        printNum(s, nums[num].lid[RIGHT]);
    }
    else
    {
        s->append(to_string(nums[num].r));
    }

    s->append("]");
}

void addRows(uint32_t row0, uint32_t row1)
{
    uint32_t row0Master = getRowMaster(row0);
    uint32_t row1Master = getRowMaster(row1);

    nums[nums_num].existent = true;
    nums[nums_num].hid = NONE;
    nums[nums_num].lid[LEFT] = row0Master;
    nums[nums_num].lid[RIGHT] = row1Master;
    nums[nums_num].row = row0;
    nums[row0Master].hid = nums_num;
    nums[row1Master].hid = nums_num;

    for (uint32_t i = 0;i < nums_num;i++)
    {
        if (nums[i].existent && nums[i].row == row1)
        {
            nums[i].row = row0;
        }
    }

    nums_num++;
}

uint32_t getRowMaster(uint32_t row)
{
    for (uint32_t i = 0;i < nums_num;i++)
    {
        if (nums[i].existent && nums[i].row == row && nums[i].hid == NONE)
        {
            return i;
        }
    }
    return 0;
}

void parseLine(string* s)
{
    uint32_t cnt = 0;
    uint32_t pos = 0;
    while (s->length())
    {
        for (uint32_t i = 0;i < s->length();i++)
        {
            if (s->c_str()[i] == '[')
            {
                cnt = 1;
                pos = i;
            }
            else if (s->c_str()[i] == ',')
            {
                if (cnt == 1)
                {
                    cnt = 2;
                }
                else
                {
                    cnt = 0;
                }
            }
            else if (s->c_str()[i] == ']') // found low layer
            {
                if (cnt == 2)
                {
                    cnt = 0;
                    i = parsePair(s, pos, (i - pos) + 1);
                }
                else
                {
                    cnt = 0;
                }
            }
        }
    }
}

uint32_t parsePair(string* s, uint32_t startpos, uint32_t len)
{
    bool empty = false;
    auto x = 0;
    string rep = "";

    string pair = s->substr(startpos, len);
    uint32_t comma = pair.find(',');
    string l = pair.substr(1, comma - 1);
    string r = pair.substr(comma + 1, pair.length() - 2 - comma);

    nums[nums_num].existent = true;
    nums[nums_num].row = rows;

    if (l.find("X") == string::npos)
    {
        nums[nums_num].l = stoi(l);
    }
    else
    {
        uint32_t l_num = stoi(l.substr(1));
        nums[nums_num].lid[LEFT] = l_num;
        nums[l_num].hid = nums_num;
    }
    if (r.find("X") == string::npos)
    {
        nums[nums_num].r = stoi(r);
    }
    else
    {
        uint32_t r_num = stoi(r.substr(1));
        nums[nums_num].lid[RIGHT] = r_num;
        nums[r_num].hid = nums_num;
    }

    rep = "X" + to_string(nums_num);
    nums_num++;

    s->replace(startpos, len, rep);

    if (s->length() == rep.length())
    {
        s->clear();
        empty = true;
    }
    //printf("%s\n", s->c_str());

    return (empty) ? (0) : (startpos + rep.length());
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
