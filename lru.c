#include "lru.h"

int getway(bool PLRU[LINES][])
{
    if (PLRU[index][0] == 1)
    {
        if (PLRU[index][1] == 1)
        {
            if (PLRU[index][2] == 1)
                return 0;
            else
                return 1;
        }
        else
        {
            if (PLRU[index][3] == 1)
                return 2;
            else
                return 3;
        }
    }
    else
    {
        if (PLRU[index][4] == 1)
        {
            if (PLRU[index][5] == 1)
                return 4;
            else
                return 5;
        }
        else
        {
            if (PLRU[index][6] == 1)
                return 6;
            else
                return 7;
        }
    }
}

int update(bool PLRU[LINES][], int way)
{
    switch (way)
    {
    case 0:
        PLRU[set][0] = 0;
        PLRU[set][1] = 0;
        PLRU[set][2] = 0;
        return 1;
    case 1:
        PLRU[set][0] = 0;
        PLRU[set][1] = 0;
        PLRU[set][2] = 1;
        return 1;
    case 2:
        PLRU[set][0] = 0;
        PLRU[set][1] = 1;
        PLRU[set][3] = 0;
        return 1;
    case 3:
        PLRU[set][0] = 0;
        PLRU[set][1] = 1;
        PLRU[set][3] = 1;
        return 1;
    case 4:
        PLRU[set][0] = 1;
        PLRU[set][4] = 0;
        PLRU[set][5] = 0;
        return 1;
    case 5:
        PLRU[set][0] = 1;
        PLRU[set][4] = 0;
        PLRU[set][5] = 1;
        return 1;
    case 6:
        PLRU[set][0] = 1;
        PLRU[set][4] = 1;
        PLRU[set][6] = 0;
        return 1;
    case 7:
        PLRU[set][0] = 1;
        PLRU[set][4] = 1;
        PLRU[set][6] = 1;
        return 1;
    }
}