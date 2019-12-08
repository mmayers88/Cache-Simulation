//MESI------------------------------------------------------------
int snoopInval(int address, cLine cache[][SET_ASS])
{
    int way;
    int index = getIndex(address);
    int SnoopRes;

    uint32_t tempTag = makeMask(21, 32) & address;
    tempTag = tempTag >> 20;
    way = findMatch(index, tempTag, cache);

    if (way == -1)
        PutSnoopResult(address, NOHIT);
        return NOHIT;
    //PutSnoopResult() NOHIT

    if (cache[index][way - 1].mesi == 'M')
    {
        //put snoop HITM
        PutSnoopResult(address, HITM);
        //GETLINE L1
        //tell L1 Invalidate
        MessageToCache(EVICTLINE, address);
        //bus op write
        BusOperation(WRITE, address, &SnoopRes); // I'm the only one to have this, sending M 
        //set mesiB I
        cache[index][way - 1].mesi = 'I';
        MessageToCache(INVALIDATELINE, address);
        return HITM;
    }
    else if (cache[index][way - 1].mesi != 'I')
    {
        //putsnoop result Hit
        PutSnoopResult(address, HIT);
        //set mesiB I and valid 0
        //message to cache "you're trash"
        cache[index][way - 1].mesi = 'I';
        cache[index][way - 1].valid = 0;
        MessageToCache(INVALIDATELINE, address);
        return HIT;
    }
    else
    {
        return NOHIT;
    }
};

int snoopRd(int address, cLine cache[][SET_ASS])
{
    int way;
    int index = getIndex(address);

    uint32_t tempTag = makeMask(21, 32) & address;
    tempTag = tempTag >> 20;
    way = findMatch(index, tempTag, cache);

    if (way == -1)
    //putsnoop NOHIT
        PutSnoopResult(address, NOHIT);
        return NOHIT;

    if (cache[index][way - 1].mesi == 'M')
    {
        //putsnoop HITM
        PutSnoopResult(address, HITM);
        //getline L1
        MessageToCache(GETLINE, address);
        //busop write
        BusOperation(WRITE, address, &SnoopRes); // I'm the only one to have this, sending M 
        //change mesiB shared
        cache[index][way - 1].mesi = 'S';
        return HITM;
    }
    else if (cache[index][way - 1].mesi != 'I')
    {
        //putsnoop hit
        PutSnoopResult(address, HIT);
        // set mesiB S
        cache[index][way - 1].mesi = 'S';
        return HIT;
    }
    else
    {
        return NOHIT;
    }
};