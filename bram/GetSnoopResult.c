//Needs to include the PMRU function header


char GetSnoopResult(unsigned int Address)
{
    return cache[getIndex(Address)][getPMRU(getIndex(Address))].mesi; //PLRUgetWay function to get the way
}