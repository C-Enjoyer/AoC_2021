// 19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX_SCANNER 50
#define MAX_BEACON  50
#define MAX_ORIENTATIONS 24
#define OVERLAP 12

typedef struct beacon
{
    int x, y, z;
}beacon_t;

typedef struct scanner
{
    bool hasPos;
    beacon_t pos;
    beacon_t beac[MAX_BEACON];
    uint32_t beac_num;
}scanner_t;

typedef struct length
{
    uint32_t len;
    uint32_t cnt;
}length_t;

void checkScanOverlap(uint32_t scan0, uint32_t scan1);
bool doOverlap(uint32_t scan0, uint32_t scan1, uint32_t* beac0, uint32_t* beac1, uint32_t* overlap_num);
void getVector(beacon_t* vect, beacon_t beac0, beacon_t beac1);
uint32_t getVectorLenght(beacon_t vect);
void addToLen(length_t* len, uint32_t* len_num, uint32_t length);
uint32_t compareLen(length_t* alen, uint32_t alen_num, length_t* blen, uint32_t blen_num);
void doXRot(beacon_t* beac);
void doYRot(beacon_t* beac);
void doRot(beacon_t* beac, uint32_t orientation);
bool vectorEqual(beacon_t vect0, beacon_t vect1);
void addVector(beacon_t* vect, beacon_t vect0, beacon_t vect1);
void addBeacon(beacon_t beac);
uint32_t getManhattan(beacon_t vect0, beacon_t vect1);

scanner_t scan[MAX_SCANNER] = { 0 };
uint32_t scan_num = 0;
uint32_t scan_solved = 0;

string orientations[MAX_ORIENTATIONS] = { "", "x", "y", "xx", "xy", "yx" , "yy" , "xxx" , "xxy" , "xyx" , "xyy" , "yxx" , "yyx" , "yyy" , "xxxy" , "xxyx" , "xxyy" , "xyxx" , "xyyy" , "yxxx" , "yyyx" , "xxxyx" , "xyxxx" , "xyyyx" };

beacon_t beacons[MAX_BEACON * MAX_SCANNER] = { 0 };
uint32_t beacons_num = 0;

int main()
{
    bool wasEmpty = false;
    while (1)
    {
        string lineIn;
        getline(cin, lineIn);

        if (lineIn.length()) 
        {
            if (lineIn.c_str()[2] != '-')
            {
                size_t semi0 = lineIn.find(',');
                size_t semi1 = lineIn.rfind(',');
                scan[scan_num].beac[scan[scan_num].beac_num].x = stoi(lineIn.substr(0, semi0));
                scan[scan_num].beac[scan[scan_num].beac_num].y = stoi(lineIn.substr(semi0 + 1, (semi1 - 1) - semi0));
                scan[scan_num].beac[scan[scan_num].beac_num].z = stoi(lineIn.substr(semi1 + 1));
                scan[scan_num].beac_num++;
            }
            wasEmpty = false;
        }
        else
        {
            if (!wasEmpty)
            {
                wasEmpty = true;
                scan_num++;
            }
            else
            {
                break;
            }
        }
    }

    scan[0].pos.x = 0;
    scan[0].pos.y = 0;
    scan[0].pos.z = 0;
    scan[0].hasPos = true;
    scan_solved++;

    while (scan_solved < scan_num)
    {
        for (uint32_t i = 0;i < scan_num; i++)
        {
            if (scan[i].hasPos)
            {
                for (uint32_t j = 0;j < scan_num; j++)
                {
                    if (!scan[j].hasPos)
                    {
                        checkScanOverlap(i, j);
                    }
                }
            }
        }
    }

    //part 1:
    /*
    for (uint32_t i = 0;i < scan_num;i++)
    {
        for (uint32_t j = 0;j < scan[i].beac_num; j++)
        {
            beacon_t beac;
            addVector(&beac, scan[i].pos, scan[i].beac[j]);
            addBeacon(beac);
        }
    }

    for (uint32_t i = 0;i < beacons_num;i++)
    {
        printf("%d,%d,%d\n", beacons[i].x, beacons[i].y, beacons[i].z);
    }

    printf("Result: %d", beacons_num);
    */

    //part 2:

    uint32_t result = 0;

    for (uint32_t i = 0;i < scan_num;i++)
    {
        for (uint32_t j = 0;j < scan_num;j++)
        {
            if (i != j)
            {
                result = max(result, getManhattan(scan[i].pos, scan[j].pos));
            }
        }
    }
    printf("Result: %d", result);
}

void checkScanOverlap(uint32_t scan0, uint32_t scan1)
{
    uint32_t beac0[MAX_BEACON] = { 0 }, beac1[MAX_BEACON] = { 0 };
    uint32_t overlap_num = 0;
    uint32_t orients[MAX_ORIENTATIONS] = { 0 };
    uint32_t orient = 0;
    if (doOverlap(scan0, scan1, beac0, beac1, &overlap_num))
    {
        bool foundOrient = false;
        for (uint32_t i = 1;i < overlap_num;i++)
        {
            beacon_t avector, bvector;
            getVector(&avector, scan[scan0].beac[beac0[0]], scan[scan0].beac[beac0[i]]);
            getVector(&bvector, scan[scan1].beac[beac1[0]], scan[scan1].beac[beac1[i]]);

            for (uint32_t j = 0;j < MAX_ORIENTATIONS;j++)
            {
                beacon_t brotvect = bvector;
                doRot(&brotvect, j);

                if (vectorEqual(avector, brotvect))
                {
                    orients[j]++;
                    if (orients[j] >= OVERLAP - 1)
                    {
                        foundOrient = true;
                        orient = j;
                    }
                }
            }
        }

        if (!foundOrient)
        {
            return;
        }

        //Rotate scanner to correct axis
        for (uint32_t i = 0;i < scan[scan1].beac_num;i++)
        {
            doRot(&scan[scan1].beac[i], orient);
        }

        //get correct scanner position
        beacon_t point;
        addVector(&point, scan[scan0].pos, scan[scan0].beac[beac0[0]]);
        getVector(&scan[scan1].pos, scan[scan1].beac[beac1[0]], point);
        scan[scan1].hasPos = true;
        scan_solved++;
    }
}



bool doOverlap(uint32_t scan0, uint32_t scan1, uint32_t* beac0, uint32_t* beac1, uint32_t* overlap_num)
{
    bool hasOverlap = false;
    *overlap_num = 0;
    for (uint32_t i = 0;i < scan[scan0].beac_num;i++)
    {
        //clear a list
        length_t alen[MAX_BEACON] = { 0 };
        uint32_t alen_num = 0;

        for (uint32_t j = 0;j < scan[scan0].beac_num;j++)
        {
            if (i != j)
            {
                //add len to a list
                beacon_t avector = { 0 };
                getVector(&avector, scan[scan0].beac[i], scan[scan0].beac[j]);
                uint32_t alength = getVectorLenght(avector);
                addToLen(alen, &alen_num, alength);
            }
        }
        //len a list completed

        for (uint32_t k = 0;k < scan[scan1].beac_num;k++)
        {
            //clear blist
            length_t blen[MAX_BEACON] = { 0 };
            uint32_t blen_num = 0;

            for (uint32_t l = 0;l < scan[scan1].beac_num;l++)
            {
                if (k != l)
                {
                    //add len to b list
                    beacon_t bvector = { 0 };
                    getVector(&bvector, scan[scan1].beac[k], scan[scan1].beac[l]);
                    uint32_t blength = getVectorLenght(bvector);
                    addToLen(blen, &blen_num, blength);
                }
            }
            //len b list completed

            //compare lists
            uint32_t overlaps = compareLen(alen, alen_num, blen, blen_num);

            //printf("From %d to %d found %d overlaps\n", i, k, overlaps);

            if (overlaps >= OVERLAP - 1) // one point is the current point...
            {
                beac0[*overlap_num] = i;
                beac1[*overlap_num] = k;
                (*overlap_num)++;
                //printf("(%d,%d,%d) = (%d,%d,%d)\n", scan[scan0].beac[i].x, scan[scan0].beac[i].y, scan[scan0].beac[i].z, scan[scan1].beac[k].x, scan[scan1].beac[k].y, scan[scan1].beac[k].z);
                hasOverlap = true;
            }
        }
    }

    return hasOverlap;
}

uint32_t getManhattan(beacon_t vect0, beacon_t vect1)
{
    return abs(vect0.x - vect1.x) + abs(vect0.y - vect1.y) + abs(vect0.z - vect1.z);
}

void addBeacon(beacon_t beac)
{
    for (uint32_t i = 0;i < beacons_num;i++)
    {
        if (vectorEqual(beacons[i], beac))
        {
            return;
        }
    }

    beacons[beacons_num] = beac;
    beacons_num++;
}

uint32_t compareLen(length_t* alen, uint32_t alen_num, length_t* blen, uint32_t blen_num)
{
    uint32_t cnt = 0;
    for (uint32_t i = 0;i < alen_num;i++)
    {
        for (uint32_t j = 0;j < blen_num;j++)
        {
            if (alen[i].len == blen[j].len)
            {
                cnt += min(alen[i].cnt, blen[j].cnt);
            }
        }
    }
    return cnt;
}

void addToLen(length_t* len, uint32_t* len_num, uint32_t length)
{
    for (uint32_t i = 0;i < *len_num;i++)
    {
        if (len[i].len == length)
        {
            len[i].cnt++;
            return;
        }
    }

    len[*len_num].cnt = 1;
    len[*len_num].len = length;
    (*len_num)++;
}

void getVector(beacon_t* vect, beacon_t beac0, beacon_t beac1)
{
    vect->x = beac1.x - beac0.x;
    vect->y = beac1.y - beac0.y;
    vect->z = beac1.z - beac0.z;
}

void addVector(beacon_t* vect, beacon_t vect0, beacon_t vect1)
{
    vect->x = vect1.x + vect0.x;
    vect->y = vect1.y + vect0.y;
    vect->z = vect1.z + vect0.z;
}

bool vectorEqual(beacon_t vect0, beacon_t vect1)
{
    return (vect0.x == vect1.x && vect0.y == vect1.y && vect0.z == vect1.z);
}

uint32_t getVectorLenght(beacon_t vect)
{
    uint32_t ret = (uint32_t) round(sqrt((double)vect.x * vect.x + (double)vect.y * vect.y + (double)vect.z * vect.z));
    return ret;
}

void doRot(beacon_t* beac, uint32_t orientation)
{
    for (uint32_t i = 0;i < orientations[orientation].length();i++)
    {
        if (orientations[orientation].c_str()[i] == 'x')
        {
            doXRot(beac);
        }
        else if (orientations[orientation].c_str()[i] == 'y')
        {
            doYRot(beac);
        }
    }
}

void doXRot(beacon_t* beac)
{
    // X -> X
    // Y -> Z
    // Z -> -Y

    int z = beac->z;
    beac->z = beac->y;
    beac->y = -z;
}

void doYRot(beacon_t* beac)
{
    // X -> Z
    // Y -> Y
    // Z -> -X

    int z = beac->z;
    beac->z = beac->x;
    beac->x = -z;
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
