#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    srand(time(NULL));
    uint64_t max = 10;

    for (int i = 0; i < 20; i++)
    {
        uint32_t r = (rand() << 16) + rand();
        printf("N: %d\n", ((uint64_t)(r * max) >> 31) + 1);
    }
    return 0;
}