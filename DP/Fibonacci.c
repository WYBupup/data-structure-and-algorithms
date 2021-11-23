#include<stdio.h>
#include<stdlib.h>
#define MAX 128
#define EMPTY 4

//naive recursion version
//time complexity O(2^n)
//space complexity O(n)
int Fibonacci_naive(int n)
{
    if(n<=0)
    {
        return -1;
    }
    if(n<=2)
    {
        return 1;
    }
    else
    {
        return Fibonacci_naive(n-1)+Fibonacci_naive(n-2);
    }
}

//Memoized DP version
//Time complexity T(n)=O(n)
//Space Complexity O(n)
int Fibonacci_MemoizedDP(int n, int *Fibonacci_series)
{   
    if(n<=0)
    {
        return -1;
    }
    if(Fibonacci_series[n]!=EMPTY)
    {
        //printf("use flag\n");
        return Fibonacci_series[n];
    }
    
    int result;
    if(n<=2)
    {
        result=1;
    }
    else
    {
        result=Fibonacci_MemoizedDP(n-1,Fibonacci_series)+Fibonacci_MemoizedDP(n-2,Fibonacci_series);
    }
    Fibonacci_series[n]=result;
    return result;
}


//Bottom up DP
//Time complexity o(n)
//space complexity o(1)
int Fibonacci_BottomUp(int n)
{
    int *Fibonacci_series=(int *)malloc(sizeof(int)*(n+1));
    if(n<=0)
    {
        return -1;
    }
    for(int i=1;i<=n;i++)
    {
        if(i<=2)
        {
            Fibonacci_series[i]=1;
        }
        else
        {
            Fibonacci_series[i]=Fibonacci_series[i-1]+Fibonacci_series[i-2];
        }
    }
    return Fibonacci_series[n];
}

int main(void)
{
    printf("Fibonacci Series:\n");
    /*
    int FibonacciSeries[MAX];
    for(int i=0;i<MAX;i++)
    {
        FibonacciSeries[i]=EMPTY;
    }
    */
    for(int i=1;i<=10;i++)
    {
        printf("%d, ",Fibonacci_BottomUp(i));
    }
    return 1;
}