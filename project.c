/*
Program Name:	project
Programmer:		Mikhail Mayers
Date:			11/13/2019
IDE:			MS Visual Studio Enterprise 2015/mingw32
Purpose:	Project for Faust, simulating a cache	                                 */
#include "helper.h"

int main(int argc, char *argv[])
{
    
    printf("starting\n\n");
    //initCache(cache);
    printf("Init Cache...\n");
    /*
    printf(" %x\n",getIndex(0b11111111111111111000000));
    //printCache(cache);
    addToCLine(0b11111111111111111000000, cache,7,'E');
    printf("added to cache\n");
    printCache(cache);
    verify(0b10101010101010101010100000101010, cache);
    printf("%x\n",0b1000000000000001000000);
    addToCLine(0b1000000000000001000000, cache, 7,'E');
    printf("%x",returnAddress(getIndex(0b1000000000000001000000),cache,7));
*/
    FILE *fp;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    parser(fp);
    printCache(cache);
    fclose(fp);
    return 0;
}