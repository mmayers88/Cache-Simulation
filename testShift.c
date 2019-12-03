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

char GetSnoopResult(unsigned int Address)
{
    int8_t check;
    check = Address & 0x3;
    printf("%d\n", check);
    if (check > 2)
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
};

int main()
{
    int address = 0xF1;

    GetSnoopResult(address);
}