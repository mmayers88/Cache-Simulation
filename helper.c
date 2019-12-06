#include "helper.h"

/*
Used to simulate a bus operation and to capture the snoop results of last
level caches of other processors
*/
void BusOperation(char BusOp, unsigned int Address, char *SnoopResult)
{
    SnoopResult = GetSnoopResult(Address);
#ifndef SILENT
    printf("BusOp: %d, Address: %x, Snoop Result: %d\n", *SnoopResult);
#endif
}
/*
Used to simulate the reporting of snoop results by other caches
*/
int GetSnoopResult(unsigned int Address)
{
    int8_t check;
    check = Address & 0x3;
    printf("\nSnoop result: %d\n", check);
    if (check > 1)
        return NOHIT;
    else
    {
        if (check == 1)
            return HITM;
        else
        {
            return HIT;
        }
    }
}
/*
Used to report the result of our snooping bus operations performed by other
caches
*/
void PutSnoopResult(unsigned int Address, char SnoopResult)
{
#ifndef SILENT
    printf("SnoopResult: Address %x, SnoopResult: %d\n", Address, SnoopResult);
#endif
}

/*
Used to simulate communication to our upper level cache
*/
void MessageToCache(char Message, unsigned int Address)
{
#ifndef SILENT
    printf("L2: %d %x\n", Message, Address);
#endif
}

int initCache(cLine cache[][SET_ASS])
{
    cLine line = {false, false, 0, 0};
    for (int j = 0; j < SET_ASS; j++)
        for (int i = 0; i < LINES; i++)
        {
            cache[i][j] = line;
        }
}

int printCache(cLine cache[][SET_ASS])
{
    for (int j = 0; j < SET_ASS; j++)
    {
        for (int i = 0; i < LINES; i++)
        {
            if (cache[i][j].valid == 1)
                printf("%x|%x|%x|%x|\n", cache[i][j].valid, cache[i][j].dirty, cache[i][j].tag, cache[i][j].byte_sel);
        }
        //printf("\n");
    }
}

int parser(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (!breakup(line))
            return -1;
    }
}

int breakup(char *line)
{
    char *token;
    int instruct[2];
    printf("%s\n", line);

    token = strtok(line, " ");

    instruct[0] = (int)strtol(token, NULL, 16);

    token = strtok(NULL, " ");
    instruct[1] = (int)strtol(token, NULL, 16);

    //printf("\n %d %x\n", instruct[0], instruct[1]);

    switchInstruction(instruct[0], instruct[1]);

    //if (switchInstruction(instruct[0], instruct[1]))
    //  return -1;
    return 1;
}

int switchInstruction(int instruct, int address)
{
    switch (instruct)
    {
    case 0: //read request from L1 data cache
        hitOrMissREAD(address, cache);
        break;
    case 1: //write request from L1 data cache
        break;
    case 2: //read request from L1 instruction cache
        break;
    case 3: //snooped invalidate command
        break;
    case 4: //snooped read request
        break;
    case 5: //snooped write request
        break;
    case 6: //snooped read with intent to modify requestnal
        break;
    case 8: //clear the cache and reset all state
        break;
    case 9: //print contents and state of each valid cache line (allow subsequent trace activity)
        break;
    default:
        return -1;
        break;
    }
}

uint32_t makeMask(uint32_t a, uint32_t b)
{
    unsigned r = 0;
    for (unsigned i = a; i <= b; i++)
        r |= 1 << i;

    return r;
}
uint32_t returnAddress(uint32_t index, cLine cache[][SET_ASS], int way)
{
    uint32_t address = 0;
    address = ((cache[index][way].tag << 20) | (index << 6) | cache[index][way].byte_sel);
};

int getIndex(uint32_t address)
{
    uint32_t index = makeMask(6, 20) & address;
    index = index >> 6;
    return index;
};

int addToCLine(uint32_t address, cLine cache[][SET_ASS], int way, char mesiB)
{
    uint32_t index = getIndex(address);
    cache[index][way].byte_sel = address & 0x3F; //lower 6 bits
    uint32_t tag = makeMask(21, 32) & address;
    cache[index][way].tag = tag >> 20;
    cache[index][way].valid = true;
    cache[index][way].dirty = true;
    cache[index][way].mesi = mesiB;
}

int verify(uint32_t address, cLine cache[][SET_ASS])
{
    uint32_t index = getIndex(address);
    uint32_t tempTag = makeMask(21, 32) & address;
    tempTag = tempTag >> 20;
    int x = findMatch(index, tempTag, cache);
    if (x > 0) //hit
        return x;
    x = findEmpty(index, cache);
    if (x < 0) //miss with empty
        return x;
    return 0; //eviction must happen
}

int hitOrMissREAD(uint32_t address, cLine cache[][SET_ASS])
{
    printf("Index: %x\n", getIndex(address));
    int way = verify(address, cache);
    int SnoopRes = GetSnoopResult(address);
    int mesiB;
    if (way == 0) //need eviction
    {
        printf("Eviction\n");
        //snoop phase

        // do something with SnoopRes
        if (SnoopRes > 1)
            mesiB = 'E';
        else
            mesiB = 'S';

        //request getway
        way = getway(pLRU[getIndex(address)]);
        //evict line
        MessageToCache(4,returnAddress(getIndex(address),cache,way));
        //add line
        addToCLine(address, cache, way, mesiB);
        //update pLRU
        update(pLRU[getIndex(address)], way);
        //send signal to L1
        MessageToCache(2,returnAddress(getIndex(address),cache,way));
        return 0;
    }
    if (way > 0) //HIT
    {
        printf("HIT\n");
        way = way - 1;
        //update pLRU
        update(pLRU[getIndex(address)], way);
        //send signal to L1
        MessageToCache(2,returnAddress(getIndex(address),cache,way));
        printf("HIT %d\n", way);
        return (way);
    }
    else //miss, but space
    {
        printf("Miss Space\n");
        way = abs(way) - 1;
        //update pLRU
        update(pLRU[getIndex(address)], way);
        //send signal to L1
        if (SnoopRes > 1)
            mesiB = 'E';
        else
            mesiB = 'S';
        char mesiB = GetSnoopResult(address);
        //add line
        addToCLine(address, cache, way, mesiB);
        MessageToCache(2,returnAddress(getIndex(address),cache,way));
        printf("miss with space %d\n", way);
        return (way);
    }
}
int emptyInLine(uint32_t index, uint32_t testTag, cLine cache[][SET_ASS])
{
    int i = 0;
    while (i < SET_ASS)
    {
        if (cache[index][i].valid == 0)
            return i; //miss
        if (cache[index][i].tag == testTag)
            return 0; //hit
        i++;
    }
    return -1; //miss
}
int findMatch(uint32_t index, uint32_t testTag, cLine cache[][SET_ASS])
{
    int i = 0;
    while (i < SET_ASS)
    {
        if (cache[index][i].tag == testTag)
            return i + 1; //hit
        i++;
    }
    return -1; //not in line
}

int findEmpty(uint32_t index, cLine cache[][SET_ASS])
{
    int i = 0;
    while (i < SET_ASS)
    {
        if (cache[index][i].valid == false)
        {
            printf("Empty line: %d", i);
            return (-1 * (i + 1)); //empty line found
        }
        i++;
    }
    return 0; //not in line
}

//MESI------------------------------------------------------------
int snoopInval(int address, cLine cache[][SET_ASS])
{
    int way;
    int index;
    
    uint32_t tempTag = makeMask(21, 32) & address;
    tempTag = tempTag >> 20;
    way = findMatch(getIndex(address), tempTag, cache);
    
    if (way == -1)
        return NOHIT;

    if (cache[index][way-1].mesi == 'M'){
        cache[index][way-1].mesi = 'I';
        //BusOperation() Maybe call BUS OPERATION HERE HITM
        return HITM;
    } else if (cache[index][way-1].mesi != 'I') {
        cache[index][way-1].mesi = 'I';
        return HIT;
    } else {
        return NOHIT;
    }
};

int snoopRd(int address, cLine cache[][SET_ASS])
{
    int way;
    int index;
    
    uint32_t tempTag = makeMask(21, 32) & address;
    tempTag = tempTag >> 20;
    way = findMatch(getIndex(address), tempTag, cache);
    
    if (way == -1)
        return NOHIT;

    if (cache[index][way-1].mesi == 'M'){
        cache[index][way-1].mesi = 'S';
        //BusOperation() Maybe call BUS OPERATION HERE HITM
        return HITM;
    } else if (cache[index][way-1].mesi != 'I') {
        cache[index][way-1].mesi = 'S';
        return HIT;
    } else {
        return NOHIT;
    }
};
// LRU
int getway(bool pLRUL[])
{
    if (pLRUL[0] == 1)
    {
        if (pLRUL[1] == 1)
        {
            if (pLRUL[2] == 1)
                return 0;
            else
                return 1;
        }
        else
        {
            if (pLRUL[3] == 1)
                return 2;
            else
                return 3;
        }
    }
    else
    {
        if (pLRUL[4] == 1)
        {
            if (pLRUL[5] == 1)
                return 4;
            else
                return 5;
        }
        else
        {
            if (pLRUL[6] == 1)
                return 6;
            else
                return 7;
        }
    }
}

int update(bool pLRUL[], int way)
{
    switch (way)
    {
    case 0:
        pLRUL[0] = 0;
        pLRUL[1] = 0;
        pLRUL[2] = 0;
        return 1;
    case 1:
        pLRUL[0] = 0;
        pLRUL[1] = 0;
        pLRUL[2] = 1;
        return 1;
    case 2:
        pLRUL[0] = 0;
        pLRUL[1] = 1;
        pLRUL[3] = 0;
        return 1;
    case 3:
        pLRUL[0] = 0;
        pLRUL[1] = 1;
        pLRUL[3] = 1;
        return 1;
    case 4:
        pLRUL[0] = 1;
        pLRUL[4] = 0;
        pLRUL[5] = 0;
        return 1;
    case 5:
        pLRUL[0] = 1;
        pLRUL[4] = 0;
        pLRUL[5] = 1;
        return 1;
    case 6:
        pLRUL[0] = 1;
        pLRUL[4] = 1;
        pLRUL[6] = 0;
        return 1;
    case 7:
        pLRUL[0] = 1;
        pLRUL[4] = 1;
        pLRUL[6] = 1;
        return 1;
    }
}