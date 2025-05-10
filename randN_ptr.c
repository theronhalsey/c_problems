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
        uint64_t r = 0;
        uint32_t *r_ptr = (void *)&r;
        _rdrand32_step(r_ptr);
        r *= max;
        r = *(r_ptr + 1) + 1;
        //printf("N: %u\n", r);
        //printf("N: %u\n", (uint32_t)*(r_ptr + 1) + 1);
    }

    QueryPerformanceCounter(&end);
    printf("Pointer math generated %llu random numbers in %.4lf seconds\n", runs, (double)(end.QuadPart-start.QuadPart) / freq.QuadPart);

    return 0;
}