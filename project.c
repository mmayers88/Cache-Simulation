/*
Program Name:	project
Programmer:		Mikhail Mayers, Abram, Fouts, Roman Minko, Bader Al
Date:			11/13/2019
IDE:			MS Visual Studio Enterprise 2015/mingw32
Purpose:	Project for Faust, simulating a cache	                                 */
#include "helper.h"

int main(int argc, char *argv[])
{
    
    printf("starting\n\n");
    FILE *fp;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    parser(fp);
    fclose(fp);
    complete();
    return 0;
}