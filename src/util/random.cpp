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

float GetRandomFloat()
{
    return static_cast<float>(static_cast<double>(rand()) / (static_cast<long long>(RAND_MAX) + 1));
}
