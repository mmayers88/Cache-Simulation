#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int getPMRU(int index);

int getPMRU(int index){ //Returns the MOST recently used way of a line
    // 0 = left :: 1 = right
    if (cache[index][0] == 0) {
        if (cache[index][1] == 0) {
            if (cache[index][2] == 0)
                return 0;   //Way 0
            else 
                return 1;   //Way 1
        } else {
            if (cache[index][3] == 0)
                return 2;   //Way 2
            else 
                return 3;   //Way 3
        }
    } else {
        if (cache[index][4] == 0) {
            if (cache[index][5] == 0)
                return 4;   //Way 4
            else 
                return 5;   //Way 5
        } else {
            if (cache[index][6] == 0)
                return 6;   //Way 6
            else 
                return 7;   //Way 7
        }
    }
};