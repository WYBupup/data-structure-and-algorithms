#include<stdio.h>
#include<stdlib.h>
//This section implement hani tower by recursion

void hanoi_tower(char a, char b, char c, int height) // a->c through b
{
	if(height==1)
	{
		printf("%c -> %c\n",a,c);
	}
	else
	{
		hanoi_tower(a,c,b,height-1);
		printf("%c -> %c\n",a,c);
		hanoi_tower(b,a,c,height-1);
	}
}

int main(void)
{
	int height;
label:	printf("Please enter the height of hanoi tower:");
	if(scanf("%d",&height)!=1)
	{
		printf("please enter the appropriate number!!\n");
		goto label;
	}
	hanoi_tower('a','b','c',height);
	
	
	return 0;
}
