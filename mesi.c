#include "mesi.h"

int snoopInval(int address, cLine cache[][SET_ASS])
{
    int way;
    int index;
    way = verify(address, cache);
    if (way == -1)
        retrun - 1;
    else
    {
        index = getIndex(address);
        cache[index][way].mesi = 'I';
        cache[index][way].valid = 0;
    }
};

int snoopRd(int address, cLine cache[][SET_ASS])
{
    int way;
    int index;
    way = verify(address, cache);
    if (way == -1)
        retrun - 1;
    else
    {
        index = getIndex(address);
        if (cache[index][way].mesi != 'I')
            cache[index][way].mesi = 'S';
    }
};
