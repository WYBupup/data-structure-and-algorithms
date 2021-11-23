#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define INIT_STACK_SIZE 100
#define INCREMENT 100
//这个代码实现了利用栈将二进制转换为十进制代码
//二进制以字符char形式存在 
typedef char Elemtype;
typedef struct 
{
	Elemtype *base;
	Elemtype *top;
	int stacksize;
}stack;

void init_stack(stack *p)
{
	p->base=(Elemtype *)malloc(sizeof(Elemtype)*INIT_STACK_SIZE);
	if(!p->base)
	{
		printf("Failed to allocate the memory!!\n");
		exit(0);
	}
	p->top=p->base;
	p->stacksize=INIT_STACK_SIZE;
}

void push(stack *p,Elemtype bit)
{
	if(p->top-p->base>=p->stacksize)
	{
		p->base=(Elemtype *)realloc(p->base,(p->stacksize+INCREMENT)*sizeof(int));
		if(!p->base)
		{
			printf("fail to allocate the memory!!\n");
			exit(0);
		}
		p->top=p->base+p->stacksize;
		p->stacksize=p->stacksize+INCREMENT;
	}
	*((p->top)++)=bit;
}

int push_num(stack *p)
{
	char binary[128];
	char bit;
	printf("Please enter the binary number:");
	fgets(binary,128,stdin);binary[strlen(binary)-1]='\0';
	for (int i=0;binary[i]!='\0';i++)
	{
		if(binary[i]<'0' || binary[i]>'1')
		{
			printf("please enter the appropriate format!!\n");
			return 0;
		}
		push(p,binary[i]);
	}
	return 1;
}

void pop(stack *p, Elemtype *bit)
{
	if(p->top>p->base)
	{
		*bit=*(--p->top);
	}
	else
	{
		printf("the stack is already empty!!\n");
	}
} 

int length(stack *p)
{
	return p->top-p->base;
}

int get_decimal(stack *p)
{
	int decimal=0;
	Elemtype bit;
	int len=length(p);
	for(int i=0;i<len;i++)
	{
		pop(p,&bit);
		decimal+=pow((double)2,(double)i)*(int)(bit-'0');
	}
	return decimal;
}

void show(stack *p)
{
	printf("the binary in the stack is:");
	Elemtype *temp=p->base;
	while(temp<p->top)
	{
		printf("%c",*(temp++));
	}
	putchar('\n');
}




int main(void)
{
	stack s;
	init_stack(&s);
	if(push_num(&s))
	{
		show(&s);
    	printf("corresponding decimal is:%d",get_decimal(&s));
    }
	
	
	return 0;
}
