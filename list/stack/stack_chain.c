#include<stdio.h>
#include<stdlib.h>
//实现了链式物理结构的栈的实现 

typedef int Elemtype;
typedef struct Node
{
	Elemtype value;
	struct Node *next;
}Node,*pointer_Node;
typedef struct 
{
	pointer_Node top;
	int length;
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
//void clear_list(stack *p); 这里destroy和clear相同 



void InitList(stack *p)
{
	p->top=NULL;
	p->length=0;
}

int ListEmpty(stack *p)
{
	if(p->length==0)
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
	pointer_Node temp;
	while(p->top!=NULL)
	{
		temp=p->top;
		p->top=p->top->next;
		free(temp);
	}
}

int GetElem(stack *p, int index, Elemtype *target)
{
	if(index>p->length || index<1)
	{
		return 0;
	}
	pointer_Node temp=p->top;
	for(int i=0;i<index-1;i++)
	{
		temp=temp->next;
	}
	*target=temp->value;
	return 1;
}

int LocateElem(stack *p, Elemtype target)
{
	pointer_Node temp=p->top;
	int index=1;
	while(temp!=NULL)
	{
		if(temp->value==target)
		{
			return index;
		}
		temp=temp->next;
		index++;
	}
	return 0;
}

void push(stack *p, Elemtype value)
{
	pointer_Node new_=(pointer_Node)malloc(sizeof(Node));
	new_->value=value;
	new_->next=p->top;
	p->top=new_;
	p->length++;
}

int pop(stack *p, int *value)
{
	if(p->length<1)
	{
		return 0;
	}
	*value=p->top->value;
	pointer_Node temp=p->top;
	p->top=p->top->next;
	free(temp);
	p->length--;
	return 1;
}

int ListLength(stack *p)
{
	return p->length;
}

void show(stack *p)
{
	printf("index       value\n");
	if(!ListEmpty(p))
	{
		pointer_Node temp=p->top;
		int index=1;
		while(temp!=NULL)
		{
			printf("  %d           %d\n",index++,temp->value);
			temp=temp->next;
		}
	}
}




int main(void)
{
	stack s;
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
					else
					{
						printf("No such element in the stack!!\n");
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
			default:printf("enter appropriate command!!\n");
		}
		printf("\n\n");
	}
	
    	
	
label:return 0;
}
