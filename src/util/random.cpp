#include "random.h"

#include <stdlib.h>

int GetRandomInt(int min, int max)
{
    return rand() % (max - min) + min;
}

int GetRandomInt(int max)
{
    return rand() % max;
}

bool GetRandomBool()
{
    return GetRandomInt(2);
}
