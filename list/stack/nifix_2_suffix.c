#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Reverse_Porland.c"
#define INIT_STACK_SIZE 100
#define INCREMENT 100
#define MAX 128
//这个代码实现了有中缀表达式输出为后缀表达式（Reverser Poland Expression）

typedef struct
{
	char *base;
	char *top;
	int length;
}operand;

void init_operand(operand *p);
void destroy_operand(operand *p);
int empty_operand(operand *p);
void push_operand(operand *p, char op);
int pop_operand(operand *p, char *op);

//Reverse_Porland.c
typedef float Elemtype;

void init_compute(stack_compute *p);
void init_number(stack_number *p);
void destroy_stack_compute(stack_compute *p);
void destroy_stack_number(stack_number *p);
void push_compute(stack_compute *p, Elemtype value);
void push_number(stack_number *p, char value);
int pop_compute(stack_compute *p, Elemtype *value);
int pop_number(stack_number *p, char *value);
int stack_empty_compute(stack_compute *p);
int stack_empty_number(stack_number *p);
int length_compute(stack_compute *p);
int length_number(stack_number *p);
int suffix_2_result(char *suffix,Elemtype *result);



void init_operand(operand *p)
{
	p->base=(char *)malloc(sizeof(char)*INIT_STACK_SIZE);
	if(!p->base)
	{
		printf("fail to allocate memory!!\n");
		exit(0);
	}
	p->top=p->base;
	p->length=INIT_STACK_SIZE;
}

void destroy_operand(operand *p)
{
	free(p->base);
	p->base=p->top=NULL;
	p->length=0;
}

int empty_operand(operand *p)
{
	if(p->base==p->top)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void push_operand(operand *p,char op)
{
	if(p->top-p->base>=p->length)
	{
		p->base=(char *)malloc(sizeof(char)*(p->length+INCREMENT));
		if(!p->base)
		{
			printf("fail to allocate the memory!!\n");
			exit(0);
		}
		p->top=p->base+p->length;
		p->length=p->length+INCREMENT;
	}
	*((p->top)++)=op;
}

int pop_operand(operand *p, char *op)
{
	if(empty_operand(p))
	{
		return 0;
	}
	*op=*(--(p->top));
	return 1;
}

int nifix_2_suffix(char *nifix, char *suffix)//succeed return 1 else return 0
{
	operand s;
	init_operand(&s);
	
	int index=0;
	int flag=0;//判断前一个字符是否为数字 
	int dot_count=0;//判断之前是否出现过小数 
	for (int i=0;nifix[i]!='\0';i++)
	{
		if(nifix[i]>='0'&&nifix[i]<='9')
		{
			suffix[index++]=nifix[i];
			if(flag==0)
			{
				flag=1;
			}
		}
		else if(nifix[i]=='.'&&flag==1&&dot_count==0)
		{
			suffix[index++]=nifix[i];
			dot_count=1;
		}
		else
		{
			if(flag==1)
			{
			    suffix[index++]=' ';
				flag=0;
				dot_count=0;
			}
		}
		
		if(nifix[i]=='+'||nifix[i]=='-')
		{
			while((*(s.top-1)=='*'||*(s.top-1)=='/'))//关键是这里乘法除法的优先级高于加减 
			{
				char op;
				pop_operand(&s,&op);
				suffix[index++]=op;
				suffix[index++]=' ';
			}
			push_operand(&s,nifix[i]);
		}
		
		
		if(nifix[i]==')')
		{
			char op;
			while(pop_operand(&s,&op))
			{
				if(op=='(')
				{
					goto label;
				}
				suffix[index++]=op;
				suffix[index++]=' ';
			}
			printf("Error format of nifix!1\n");
			return 0;
			label:;
		}
		
		if(nifix[i]=='*'||nifix[i]=='/'||nifix[i]=='(')
		{
			push_operand(&s,nifix[i]);
			
		}
	}
	suffix[index++]=' ';
	char op;
	while(pop_operand(&s,&op))
	{
		suffix[index++]=op;
		suffix[index++]=' ';
	}
	suffix[index]='\0';
	destroy_operand(&s);
	return 1;
}

int main(void)
{
	char nifix[MAX];
	char suffix[MAX];
	printf("Please enter the expression:");
	fgets(nifix, MAX, stdin);nifix[strlen(nifix)-1]='\0';
	printf("nifix:%s\n",nifix);
	if(nifix_2_suffix(nifix, suffix))
	{
		printf("suffix:%s\n",suffix);
		Elemtype result;
		if(suffix_2_result(suffix,&result))
		{
			printf("result:%f",result);
		}
	}
	return 0;
 } 
