
int getway(bool pLRUL[])
{
    if (pLRUL[0] == 1)
    {
        if (pLRUL[1] == 1)
        {
            if (pLRUL[2] == 1)
                return 0;
            else
                return 1;
        }
        else
        {
            if (pLRUL[3] == 1)
                return 2;
            else
                return 3;
        }
    }
    else
    {
        if (pLRUL[4] == 1)
        {
            if (pLRUL[5] == 1)
                return 4;
            else
                return 5;
        }
        else
        {
            if (pLRUL[6] == 1)
                return 6;
            else
                return 7;
        }
    }
}

int update(bool pLRUL[], int way)
{
    switch (way)
    {
    case 0:
        pLRUL[0] = 0;
        pLRUL[1] = 0;
        pLRUL[2] = 0;
        return 1;
    case 1:
        pLRUL[0] = 0;
        pLRUL[1] = 0;
        pLRUL[2] = 1;
        return 1;
    case 2:
        pLRUL[0] = 0;
        pLRUL[1] = 1;
        pLRUL[3] = 0;
        return 1;
    case 3:
        pLRUL[0] = 0;
        pLRUL[1] = 1;
        pLRUL[3] = 1;
        return 1;
    case 4:
        pLRUL[0] = 1;
        pLRUL[4] = 0;
        pLRUL[5] = 0;
        return 1;
    case 5:
        pLRUL[0] = 1;
        pLRUL[4] = 0;
        pLRUL[5] = 1;
        return 1;
    case 6:
        pLRUL[0] = 1;
        pLRUL[4] = 1;
        pLRUL[6] = 0;
        return 1;
    case 7:
        pLRUL[0] = 1;
        pLRUL[4] = 1;
        pLRUL[6] = 1;
        return 1;
    }
}

