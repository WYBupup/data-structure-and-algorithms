#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 10
#define INCREMENT 10
//实现了线性物理结构的栈的实现 实现了动态的地址分配 
typedef int Elemtype;
typedef struct 
{
	Elemtype *top;
	Elemtype *base;
	int stacksize;
}stack;


void InitList(stack *p);
int ListEmpty(stack *p); //if empty return 1 else return 0
void Destroy_list(stack *p);
int GetElem(stack *p, int index, int *target);//index is not start from 0;return 0 if fail else return 1  from the top of the stack
int LocateElem(stack *p, int target);//find e in list.succeed:return index+1;else return 0; from the top of the stack
void push(stack *p, int value);//insert new element
int pop(stack *p, int *value);//succeed return 1 else return 0
int ListLength(stack *p);
void show(stack *p);
void clear_list(stack *p);


void InitList(stack *p)
{
	p->base=(Elemtype *)malloc(sizeof(Elemtype)*STACK_INIT_SIZE);
	if(!p->base)
	{
		printf("Fail to allocate the memory!!\n");
		exit(0);
	}
	p->top=p->base;
	p->stacksize=STACK_INIT_SIZE;
}

int ListEmpty(stack *p)
{
	if(p->top==p->base)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Destroy_list(stack *p)
{
	int len=p->stacksize;//要清理每一个元素即使尚未赋值 
	for (int i=0;i<len;i++,p->base++)
	{
		free(p->base);
	}
	p->base=p->top=NULL;
	p->stacksize=0;
	printf("Clear the memory for the stack!!\n");
}

int GetElem(stack *p, int index, Elemtype *target)
{
	if(index>p->top-p->base)
	{
		printf("Out of range of the stack!!\n");
		return 0;
	}
	*target=*(p->top-index);
	return 1;
}

int LocateElem(stack *p, Elemtype target)
{
	int i;
	for(i=1;(p->top-i)>=p->base;i++)
	{
		if(*(p->top-i)==target)
		{
			return i;
		}
	}
	return 0;
}

void push(stack *p, Elemtype value)
{
	if(p->top-p->base>=p->stacksize)
	{
		p->base=(Elemtype *)malloc(sizeof(Elemtype)*(p->stacksize+INCREMENT));
		p->top=p->base+p->stacksize;
		p->stacksize=p->stacksize+INCREMENT;
	}
	*(p->top++)=value;
}

int pop(stack *p, Elemtype *value)
{
	if(ListEmpty(p))
	{
		return 0;
	}
	
	*value=*(--p->top);
	return 1;
}

int ListLength(stack *p)
{
	return (int)(p->top-p->base);
}

void show(stack *p)
{
	printf("index       value\n");
	if(!ListEmpty(p))
	{
		int index=1;
		while((p->top-index)>=p->base)
		{
			printf("  %d           %d\n",index,*(p->top-index));
			index++;
		}
	}
}

void clear_list(stack *p)
{
	p->top=p->base;
}



int main(void)
{
	stack s;;
	InitList(&s);
	int command;
	printf("The stack is initialized!!\n");
	printf("---------------------------------------List-------------------------------------------\n");
	printf("           Command code                                     Function\n");
	printf("                0                                          destroy List\n");
	printf("                1                                 tell whether the list is empty or not\n");
	printf("                2                                  get element of list in terms of index\n");
    printf("                3                                  Locate the element in terms of value\n");
    printf("                4                                              push\n");
    printf("                5                                               pop\n");
    printf("                6                                    show the length of the list\n");
    printf("                7                                           show the list\n");
    printf("                8                                           clear the list\n");
    printf("\n\n\n");
    
	while(1)
	{
		printf("Enter corresponding command code:");scanf("%d",&command);getchar();
		switch(command)
		{
			case 0:
				{
					Destroy_list(&s);
					goto label;
				}
			case 1:
				{
					if(ListEmpty(&s))
					{
						printf("The list is empty!\n");
					}
					else
					{
						printf("The list is not empty!!!\n");
					}
					break;
				}
			case 2:
				{
					int index;
					Elemtype value;
					printf("enter the index of the elemnet you want to choose:");scanf("%d",&index);getchar();
					if(GetElem(&s,index,&value))
					{
						printf("index:%d       value:%d\n",index,value);
					}
					break;
				}
			case 3:
				{
					int index;
					Elemtype value;
					printf("enter the value of the element you want to look for:");scanf("%d",&value);getchar();
					if(index=LocateElem(&s,value))
					{
						printf("index:%d       value:%d\n",index,value);
					}
					else
					{
						printf("there is no such element in the list!!\n");
					}
					break;
				}
			case 4:
			    {
			    	Elemtype value;
			    	printf("enter the value of the element you want to insert :");scanf("%d",&value);getchar();
			    	push(&s,value);
			    	break;
				}
			case 5:
				{
					Elemtype deleted_value;
					if(pop(&s,&deleted_value))
					{
						printf("Deleted value:%d\n",deleted_value);
					}
					else
					{
						printf("The stack is empty!!\n");
					}
					break;
				}
			case 6:
				{
					printf("The length of the list:%d\n",ListLength(&s));
					break;
				}
			case 7:
				{
					show(&s);
					break;
				}
			case 8:
				{
					clear_list(&s);
					break;
				}
			default:printf("enter appropriate command!!\n");
		}
		printf("\n\n");
	}
	
    	
	
label:return 0;
}
