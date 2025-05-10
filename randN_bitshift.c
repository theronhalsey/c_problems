#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <immintrin.h>

int main()
{
    uint64_t max = 10;
    uint64_t runs = 1000000000;
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    
    for (int i = 0; i < runs; i++)
    {
        uint32_t r;
        uint64_t n;
        _rdrand32_step(&r);
        n = ((r * max) >> 32) + 1;
        //printf("N: %lu\n", n);
        //printf("N: %lu\n", ((uint64_t)(r * max) >> 32) + 1);
    }

    QueryPerformanceCounter(&end);
    printf("Bitshifting generated %llu random numbers in %.4lf seconds\n", runs, (double)(end.QuadPart-start.QuadPart) / freq.QuadPart);

    return 0;
}