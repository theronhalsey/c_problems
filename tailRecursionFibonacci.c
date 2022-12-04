#include <stdio.h>
#include <time.h>
#include <windows.h>

unsigned long long badFibonacci(unsigned int num);
unsigned long long tailFibonacci(unsigned int num);
unsigned long long tailRecursiveFibonacci(unsigned int num, unsigned long long previous, unsigned long long current);


int main(void)
{
    clock_t start, end;
    double tailFibTime, badFibTime;

    start = clock();
    for (unsigned int i = 1; i <= 45; i++)
        printf("Bad Fibonacci %2d = %lld\n", i, badFibonacci(i));
    end = clock();
    badFibTime = (double) (end-start) / CLOCKS_PER_SEC;
    Sleep(2000);
    puts("");

    start = clock();
    for (unsigned int i = 1; i <= 93; i++)
        printf("Fibonacci %2d = %lld\n", i, tailFibonacci(i));
    end = clock();
    tailFibTime = (double) (end-start) / CLOCKS_PER_SEC;
    puts("");

    printf("Bad Fibonacci Time: %.4lf seconds\nTail Fibonacci Factorial Time: %.4lf seconds\n", badFibTime, tailFibTime);

}

unsigned long long badFibonacci(unsigned int num)
{
    if(num == 1)
        return 0;
    if(num == 2)
        return 1;
    return badFibonacci(num - 1) + badFibonacci(num - 2);
}

unsigned long long tailFibonacci(unsigned int num)
{
    if(num == 1)
        return 0;
    if(num == 2)
        return 1;
    return tailRecursiveFibonacci(num, 1, 1);

}

unsigned long long tailRecursiveFibonacci(unsigned int num, unsigned long long previous, unsigned long long current)
{
    if(num <= 3)
        return current;
    tailRecursiveFibonacci(--num, current, previous + current);
}


