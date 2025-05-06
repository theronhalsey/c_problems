#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>

#define FIB_NUM_TAIL 92
#define FIB_NUM_STD 46

unsigned long long stdRecursiveFibonacci(unsigned int num);
unsigned long long tailRecursiveFibonacci(unsigned int num, unsigned long long previous, unsigned long long current);

int main(void)
{
    double tailFibTime, stdFibTime;
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    // run fibonacci calculation with tail recursion
    QueryPerformanceCounter(&start);
    printf("\nTail Fibonacci(%2d) = %lld\n", FIB_NUM_TAIL, tailRecursiveFibonacci(FIB_NUM_TAIL, 1, 2));
    QueryPerformanceCounter(&end);
    tailFibTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;

    // run fibonacci calculation with standard recursion
    QueryPerformanceCounter(&start);
    printf(" Std Fibonacci(%2d) = %lld\n", FIB_NUM_STD, stdRecursiveFibonacci(FIB_NUM_STD));
    QueryPerformanceCounter(&end);
    stdFibTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

    printf("\n    Tail Fibonacci Time: %.4lf MILLIseconds\nStandard Fibonacci Time: %.4lf seconds\n", tailFibTime, stdFibTime);
}

unsigned long long stdRecursiveFibonacci(unsigned int num)
{
    if (num <= 2)
        return 1;
    return stdRecursiveFibonacci(num - 1) + stdRecursiveFibonacci(num - 2);
}

unsigned long long tailRecursiveFibonacci(unsigned int num, unsigned long long previous, unsigned long long current)
{
    switch (num)
    {
    case 1:
        return 1;
    case 3:
        return current;
    default:
        tailRecursiveFibonacci(--num, current, previous + current);
    }
}
