#include <stdio.h>
#include <time.h>
#include <windows.h>

unsigned long long badFactorial(unsigned int num);
unsigned long long tailRecursiveFactorial(unsigned int num, unsigned long long accumulator);

#define MAX_FACT 20

int main(void)
{
    double tailFactTime, badFactTime;
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&start);
    for (unsigned int i = 0; i <= MAX_FACT; i++)
        printf("Tail %2d! = %lld\n", i, tailRecursiveFactorial(i, 1));
    QueryPerformanceCounter(&end);
    tailFactTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

    puts("");

    QueryPerformanceCounter(&start);
    for (unsigned int i = 0; i <= MAX_FACT; i++)
        printf("Bad %2d! = %lld\n", i, badFactorial(i));
    QueryPerformanceCounter(&end);
    badFactTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

    printf("\nTail Recursive Factorial Time: %.4lf seconds\nBad Factorial Time: %.4lf seconds\n", tailFactTime, badFactTime);
}

unsigned long long badFactorial(unsigned int num)
{
    if (num == 0)
        return 1;
    return num * badFactorial(num - 1);
}

unsigned long long tailRecursiveFactorial(unsigned int num, unsigned long long accumulator)
{
    if (num <= 1)
        return accumulator;
    tailRecursiveFactorial(--num, accumulator * num);
}