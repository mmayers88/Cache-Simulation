#include "helper.h"


/*
Used to simulate a bus operation and to capture the snoop results of last
level caches of other processors
*/
void BusOperation(char BusOp, unsigned int Address, char *SnoopResult);
SnoopResult = GetSnoopResult(Address)
#ifndef SILENT
printf("BusOp: %d, Address: %h, Snoop Result: %d\n",*SnoopResult);
#endif
}
/*
Used to simulate the reporting of snoop results by other caches
*/
char GetSnoopResult(unsigned int Address)
{


}
/*
Used to report the result of our snooping bus operations performed by other
caches
*/
void PutSnoopResult(unsigned int Address, char SnoopResult)
{
#ifndef SILENT
printf("SnoopResult: Address %h, SnoopResult: %d\n", Address,SnoopResult);
}
#endif
/*
Used to simulate communication to our upper level cache
*/
void MessageToCache(char Message, unsigned int Address)
{
#ifndef SILENT
printf("L2: %d %h\n", Message, Address);
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
            printf("%x|%x|%x|%x|\n", cache[i][j].valid, cache[i][j].dirty, cache[i][j].tag, cache[i][j].byte_sel);
        }
        printf("\n");
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
    printf("%s", line);

    token = strtok(line, " ");

    instruct[0] = (int)strtol(token, NULL, 16);

    token = strtok(NULL, " ");
    instruct[1] = (int)strtol(token, NULL, 16);

    printf("\n %d %x\n", instruct[0], instruct[1]);

    if (switchInstruction(instruct[0], instruct[1]))
        return -1;
}

int switchInstruction(int instruct, int address)
{
    switch (instruct)
    {
    case 0: //read request from L1 data cache
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
int addToCLine(uint32_t address, cLine cache[][SET_ASS], int way)
{
    uint32_t index = makeMask(7, 20) & address;
    //index = index >> 6;
    index = 2;
    cache[index][way].byte_sel = address & 0x3F; //lower 6 bits
    uint32_t tag = makeMask(21, 32) & address;
    cache[index][way].tag = tag >> 20;
    cache[index][way].valid = true;
    cache[index][way].dirty = true;
}

int verify(uint32_t address, cLine cache[][SET_ASS])
{
    uint32_t index = makeMask(7, 20) & address;
    //index = index >> 6;
    index = 2;
    uint32_t tempTag = makeMask(21, 32) & address;
    tempTag = tempTag >> 20;
    int x = emptyInLine(index, tempTag, cache);
    if (x >= 0)
    { // looking for empty place
        int y = findMatch(index, tempTag, cache);
        if (y >= 0)
        {
            printf("empty but, hit Baby! %d\n",y);
            return y;
        }
        else
        {
            printf("miss with space %d\n",x);
            return x;
        }
    }
    else
    {
        printf("miss, line full\n");
        return -1;
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
    return -1;//miss
}
int findMatch(uint32_t index, uint32_t testTag, cLine cache[][SET_ASS])
{
    int i = 0;
    while (i < SET_ASS)
    {
        if (cache[index][i].tag == testTag)
            return i; //hit
        i++;
    }
    return -1; //not in line
}

int findEmpty(uint32_t index,cLine cache[][SET_ASS])
{
    int i = 0;
    while (i < SET_ASS)
    {
        if (cache[index][i].valid == false)
        {
            printf("\n%d\n",i);
            printf("Empty line: %d",i);
            return i; //hit
        }
        i++;
    }
    return -1; //not in line
}