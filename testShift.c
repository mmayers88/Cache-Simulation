#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include "helper.h"

cLine cache2[3][4];

int main()
{
    int way;
    initCache(cache2);
    printCache(cache2);
    printf(" %x\n", getIndex(0b11111111111111111000000));
    way = verify(0b1000000, cache2);
    addToCLine(0b1000000, cache, way);
    printCache(cache2);
}