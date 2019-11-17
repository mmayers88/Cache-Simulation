/*
Program Name:	project
Programmer:		Mikhail Mayers
Date:			11/13/2019
IDE:			MS Visual Studio Enterprise 2015/mingw32
Purpose:	Project for Faust, simulating a cache	                                 */
#include "helper.h"

int main(int argc, char *argv[])
{
    initCache(cache);
    addToCLine(0b10101010101010101010100000101010, cache,1);
    printCache(cache);
    verify(0b10101010101010101010100000101010, cache);
    //findEmpty(0b10101010101010101010100000101010, cache);

    FILE *fp;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    parser(fp);

    fclose(fp);
    return 0;
}