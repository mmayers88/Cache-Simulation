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
    long int dat;
    int tag = 0x45;
    int index = 0x29;
    int bits = 0x6;

    dat = ((tag << 21)|(index << 6)| bits);
    printf("%lx\n",dat);
}