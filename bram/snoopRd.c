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