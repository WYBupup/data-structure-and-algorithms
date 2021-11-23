#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INIT_STACK_SIZE 100
#define INCREMENT 100
#define MAX 128
//利用线性stack实现逆波兰算法 支持小数计算 
//一个栈存储输入的数据，一个站用于将输入的数据转换为数字 
typedef float Elemtype;
typedef struct 
{
	Elemtype *base;
	Elemtype *top;
	int length;
}stack_compute;

typedef struct 
{
	char *base;
	char *top;
	int length;
}stack_number;



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


void init_compute(stack_compute *p)
{
	p->base=(Elemtype *)malloc(sizeof(Elemtype)*INIT_STACK_SIZE);
	if(!p->base)
	{
		printf("Fail to allocate memory!!\n");
		exit(0);
	}
	p->top=p->base;
	p->length=INIT_STACK_SIZE;
}

void init_number(stack_number *p)
{
	p->base=(char *)malloc(sizeof(char)*INIT_STACK_SIZE);
	if(!p->base)
	{
		printf("Fail to allocate memory!!\n");
		exit(0);
	}
	p->top=p->base;
	p->length=INIT_STACK_SIZE;
}

void destory_stack_compute(stack_compute *p)
{
	Elemtype *temp;
	while(p->base<p->top)
	{
		temp=p->base;
		p->base++;
		free(temp);
	}
	p->base=p->top=NULL;
	p->length=0;
}

void destory_stack_number(stack_number *p)
{
	char *temp;
	while(p->base<p->top)
	{
		temp=p->base;
		p->base++;
		free(temp);
	}
	p->base=p->top=NULL;
	p->length=0;
}

void push_compute(stack_compute *p, Elemtype value)
{
	if(p->top-p->base>=p->length)
	{
		p->base=(Elemtype *)malloc(sizeof(Elemtype)*(p->length+INCREMENT));
		if(!p->base)
		{
			printf("Fail to allocate memory!!\n");
			exit(0);
	    }
	    p->top=p->base+p->length;
	    p->length=p->length+INCREMENT;
	}
	
	
    *((p->top)++)=value;
	
}

void push_number(stack_number *p, char value)
{
	if(p->top-p->base>=p->length)
	{
		p->base=(char *)malloc(sizeof(char)*(p->length+INCREMENT));
		if(!p->base)
		{
			printf("Fail to allocate memory!!\n");
			exit(0);
	    }
	    p->top=p->base+p->length;
	    p->length=p->length+INCREMENT;
	}
	
	
    *((p->top)++)=value;
	
}

int pop_compute(stack_compute *p, Elemtype *value)
{
	if(stack_empty_compute(p))
	{
		return 0;
	}
	
	*value=*(--(p->top));
}

int pop_number(stack_number *p, char *value)
{
	if(stack_empty_number(p))
	{
		return 0;
	}
	
	*value=*(--(p->top));
}

int stack_empty_compute(stack_compute *p)
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

int stack_empty_number(stack_number *p)
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

int length_compute(stack_compute *p)
{
	return p->top-p->base;
}

int length_number(stack_number *p)
{
	return p->top-p->base;
}

int suffix_2_result(char *suffix,Elemtype *result)
{
	stack_compute compute;
	stack_number number;
	init_compute(&compute);
	init_number(&number);
	
	int flag=0;//判断前面的字符是否为数字 
	int dot_count=0;//判断小数时用于判定之前是否出现过小数点 
	
	for (int i=0;suffix[i]!='\0';i++)
	{
		if((suffix[i]>='0' && suffix[i]<='9'))
		{
			push_number(&number,suffix[i]);
			printf("push %c to number\n",suffix[i]);
			if(flag==0)
			{
				flag=1;
			}
		}
		else if(suffix[i]=='.'&&flag==1&&dot_count==0)
		{
			push_number(&number,suffix[i]);
			printf("push %c to number\n",suffix[i]);
			dot_count=1;
		}
		else if(flag==1)
		{
			Elemtype magnitude=1;
			Elemtype num=0;
			char temp;
			while(pop_number(&number,&temp))
			{
				if(temp=='.')
				{
					num=num/magnitude;
					magnitude=1;
				}
				else
				{
					num+=magnitude*(float)(temp-'0');
			    	magnitude=magnitude*10;
				}
				
			}
			push_compute(&compute,num);
			printf("push %f to compute!\n",num);
			flag=0;
			dot_count=0;
		}
	
		
		if(suffix[i]=='+')
		{
			if(length_compute(&compute)<2)
			{
				printf("error of the format+!!\n");
				return 0;
			}
			Elemtype num1,num2;
			pop_compute(&compute,&num1);
			printf("get %f from number!\n",num1);
			pop_compute(&compute,&num2);
			printf("get %f from number!\n",num2);
			push_compute(&compute,num1+num2);
			printf("push %f to compute!\n", num1+num2);
		}
		
		if(suffix[i]=='-')
		{
			if(length_compute(&compute)<2)
			{
				printf("error of the format-!!\n");
				return 0;
			}
			Elemtype num_delete,num_deleted;
			pop_compute(&compute,&num_delete);
			printf("get %f from number!\n",num_delete);
			pop_compute(&compute,&num_deleted);
			printf("get %f from number!\n",num_deleted);
			push_compute(&compute,num_deleted-num_delete);
			printf("push %f to compute!\n",num_deleted-num_delete);
		}
		
		if(suffix[i]=='*')
		{
			if(length_compute(&compute)<2)
			{
				printf("error of the format*!!\n");
				return 0;
			}
			Elemtype num1,num2;
			pop_compute(&compute,&num1);
			printf("get %f from number!\n",num1);
			pop_compute(&compute,&num2);
			printf("get %f from number!\n",num2);
			push_compute(&compute,num1*num2);
			printf("push %f to compute!\n",num1*num2);
		}
		
		if(suffix[i]=='/')
		{
			if(length_compute(&compute)<2)
			{
				printf("error of the format/!!\n");
				return 0;
			}
			Elemtype num_divide,num_divided;
			pop_compute(&compute,&num_divide);
			printf("get %f from number!\n",num_divide);
			pop_compute(&compute,&num_divided);
			printf("get %f from number!\n",num_divided);
			if(num_divide==0)
			{
				printf("number cant be divided by 0\n");
				return 0;
			}
			push_compute(&compute,num_divided/num_divide);
			printf("push %f to compute!\n",num_divided/num_divide);
		}
		
	}
	printf("length of compute:%d\n",length_compute(&compute));
	printf("length of number:%d\n",length_number(&number));
	
	if(length_compute(&compute)>1 || !stack_empty_number(&number))//
	{
		printf("Format error out !!\n");
		return 0;
	}
	pop_compute(&compute,result);
	destory_stack_compute(&compute);
	destory_stack_number(&number);
	return 1;
	
}



#if 0
int main(void)
{
	/*
	stack_compute compute;
	stack_number number;
	init_compute(&compute);
	init_number(&number);
	*/
	
	char suffix[MAX];
	printf("please enter the Reverse Porland expression:");
	fgets(suffix,MAX,stdin);suffix[strlen(suffix)-1]='\0';
	Elemtype result;
	if(suffix_2_result(suffix, &result))
	{
		printf("result:%f",result);
	}
	
	/*
	int flag=0;//判断前面的字符是否为数字 
	int dot_count=0;//判断小数时用于判定之前是否出现过小数点 
	
	for (int i=0;str[i]!='\0';i++)
	{
		if((str[i]>='0' && str[i]<='9'))
		{
			push_number(&number,str[i]);
			printf("push %c to number\n",str[i]);
			if(flag==0)
			{
				flag=1;
			}
		}
		else if(str[i]=='.'&&flag==1&&dot_count==0)
		{
			push_number(&number,str[i]);
			printf("push %c to number\n",str[i]);
			dot_count=1;
		}
		else if(flag==1)
		{
			Elemtype magnitude=1;
			Elemtype num=0;
			char temp;
			while(pop_number(&number,&temp))
			{
				if(temp=='.')
				{
					num=num/magnitude;
					magnitude=1;
				}
				else
				{
					num+=magnitude*(float)(temp-'0');
			    	magnitude=magnitude*10;
				}
				
			}
			push_compute(&compute,num);
			printf("push %f to compute!\n",num);
			flag=0;
			dot_count=0;
		}
	
		
		if(str[i]=='+')
		{
			if(length_compute(&compute)<2)
			{
				printf("error of the format+!!\n");
				goto label;
			}
			Elemtype num1,num2;
			pop_compute(&compute,&num1);
			printf("get %f from number!\n",num1);
			pop_compute(&compute,&num2);
			printf("get %f from number!\n",num2);
			push_compute(&compute,num1+num2);
			printf("push %f to compute!\n", num1+num2);
		}
		
		if(str[i]=='-')
		{
			if(length_compute(&compute)<2)
			{
				printf("error of the format-!!\n");
				goto label;
			}
			Elemtype num_delete,num_deleted;
			pop_compute(&compute,&num_delete);
			printf("get %f from number!\n",num_delete);
			pop_compute(&compute,&num_deleted);
			printf("get %f from number!\n",num_deleted);
			push_compute(&compute,num_deleted-num_delete);
			printf("push %f to compute!\n",num_deleted-num_delete);
		}
		
		if(str[i]=='*')
		{
			if(length_compute(&compute)<2)
			{
				printf("error of the format*!!\n");
				goto label;
			}
			Elemtype num1,num2;
			pop_compute(&compute,&num1);
			printf("get %f from number!\n",num1);
			pop_compute(&compute,&num2);
			printf("get %f from number!\n",num2);
			push_compute(&compute,num1*num2);
			printf("push %f to compute!\n",num1*num2);
		}
		
		if(str[i]=='/')
		{
			if(length_compute(&compute)<2)
			{
				printf("error of the format/!!\n");
				goto label;
			}
			Elemtype num_divide,num_divided;
			pop_compute(&compute,&num_divide);
			printf("get %f from number!\n",num_divide);
			pop_compute(&compute,&num_divided);
			printf("get %f from number!\n",num_divided);
			if(num_divide==0)
			{
				printf("number cant be divided by 0\n");
				goto label;
			}
			push_compute(&compute,num_divided/num_divide);
			printf("push %f to compute!\n",num_divided/num_divide);
		}
		
	}
	printf("length of compute:%d\n",length_compute(&compute));
	printf("length of number:%d\n",length_number(&number));
	
	if(length_compute(&compute)>1 || !stack_empty_number(&number))//
	{
		printf("Format error out !!\n");
		goto label;
	}
	Elemtype result;
	pop_compute(&compute,&result);
	printf("result:%f\n",result);
	
	
	
	
	
label:destory_stack_compute(&compute);
	destory_stack_number(&number);
	*/
	return 0;
 } 
#endif
