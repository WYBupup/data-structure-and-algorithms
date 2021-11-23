#include<stdio.h>
#include<stdlib.h>
//利用递归实现斐波那契数列
int Fibonacci(int index)
{
	if(index<=2)
	{
		return 1;
	}
	return Fibonacci(index-1)+Fibonacci(index-2);
}


int main(void)
{
	int num;
	printf("Please enter the number of the Fibonacci List!!:");
	if(scanf("%d",&num)!=1)
	{
		printf("Number not corrected entered!!\n");
		exit(EXIT_FAILURE);
	}
	getchar();
	int fib[num];
	for(int i=1;i<=num;i++)
	{
		*(fib+i-1)=Fibonacci(i);
	}
	for (int i=0;i<num;i++)
	{
		printf("%d ",fib[i]);
	}
	return 0;
 } 
