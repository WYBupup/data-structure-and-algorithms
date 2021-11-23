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

char get_hex_char(int num)
{
	if(num>=0 && num<=9)
	{
		return (char)(num+'0');
	}
	if(num>=10 && num<=15)
	{
		return (char)(num-10+'A');
	}
}


void get_hexadecimal(stack *p_bin,stack *p_hex)
{
	int len=length(p_bin);
	Elemtype bit;
	int hex=0;
	for (int i=0;i<len;i++)
	{
		pop(p_bin,&bit);
		hex+=pow(2.0,(double)(i%4))*(int)(bit-'0');
		if(i%4==3 || i==len-1)
		{
			push(p_hex,get_hex_char(hex));
			hex=0;
		}
	}
}

void show(stack *p,int orientation)//1:from top of the stack;0:from 
{
	if(orientation==0)
	{
    	Elemtype *temp=p->base;
    	while(temp<p->top)
    	{
    		printf("%c",*(temp++));
    	}   
	}
	if(orientation==1)
	{
		Elemtype *temp=p->top-1;
    	while(temp>=p->base)
    	{
    		printf("%c",*(temp--));
    	} 
	}
	putchar('\n');
}




int main(void)
{
	stack bin,hex;
	init_stack(&bin);
	init_stack(&hex);
	if(push_num(&bin))
	{
		printf("the binary is:");
		show(&bin,0);
    }
    else
    {
    	return 0;
	}
	get_hexadecimal(&bin,&hex);
	printf("corresponding hexadecimal is:");
	show(&hex,1);
	
	
	return 0;
}
