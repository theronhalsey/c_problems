#include <stdio.h>
#include <time.h>
#include <windows.h>

unsigned long long badFactorial(unsigned int num);
unsigned long long tailFactorial(unsigned int num);
unsigned long long tailRecursiveFactorial(unsigned int num, unsigned long long accumulator);


int main(void)
{
    clock_t start, end;
    double tailFactTime, badFactTime;

    start = clock();
    for (unsigned int i = 0; i <= 20; i++)
        printf("Tail %2d! = %lld\n", i, tailFactorial(i));
    end = clock();
    tailFactTime = (double) (end-start) / CLOCKS_PER_SEC;
    Sleep(2000);
    puts("");

    start = clock();
    for (unsigned int i = 1; i <= 20; i++)
        printf("Bad %2d = %lld\n", i, badFactorial(i));
    end = clock();
    badFactTime = (double) (end-start) / CLOCKS_PER_SEC;
    Sleep(2000);
    puts("");

     printf("Tail Recursive Factorial Time: %.4lf seconds\nBad Factorial Time: %.4lf seconds\n", tailFactTime, badFactTime);
}

unsigned long long badFactorial(unsigned int num)
{
    if(num == 0)
        return 1;
    return num * badFactorial(num - 1);
}

unsigned long long tailFactorial(unsigned int num)
{
    if(num <= 0)
        return 1;
    return tailRecursiveFactorial(num, 1);
}

unsigned long long tailRecursiveFactorial(unsigned int num, unsigned long long accumulator)
{
    if(num == 1)
        return accumulator;
    tailRecursiveFactorial(--num, accumulator * num);
}
