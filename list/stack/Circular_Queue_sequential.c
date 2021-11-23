#include<stdio.h>
#include<stdlib.h>
#define MAX 5;
//实现了线性存储结构的循环队列 牺牲一个元素用于判定元素是否已满 
typedef int Elemtype;
typedef struct
{
    int length;
	int front;
	int rear;
	Elemtype *base;	
}Circular_Queue;

void InitList(Circular_Queue *p);
int ListEmpty(Circular_Queue *p); //if empty return 1 else return 0
void Destroy_list(Circular_Queue *p);
int GetElem(Circular_Queue *p, int index, Elemtype *target);//index is not start from 0;return 0 if fail else return 1  from the front of the Queue
int LocateElem(Circular_Queue *p, Elemtype target);//find e in list.succeed:return index+1;else return 0; from the front of the Queue
int push(Circular_Queue *p, Elemtype value);//insert new element at the rear of the queue
int pop(Circular_Queue *p, Elemtype *value);//succeed return 1 else return 0 get elemtype at the top of the Queue
int QueueLength(Circular_Queue *p);
void show(Circular_Queue *p);
void clear_list(Circular_Queue *p);



void InitList(Circular_Queue *p)
{
	p->length=MAX;
	p->base=(Elemtype *)malloc(sizeof(Elemtype)*p->length);
	if(!p->base)
	{
		printf("Fail to alllocate the memory!!\n");
		exit(0);
	}
	p->front=p->rear=0;
}

int ListEmpty(Circular_Queue *p)
{
	if(p->front==p->rear)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Destroy_list(Circular_Queue *p)
{
	free(p->base);
	p->base=NULL;
}

int GetElem(Circular_Queue *p, int index, Elemtype *target)
{
	if(QueueLength(p)<index)
	{
		printf("Out of the range of the queue\n");
		return 0;
	}
	int temp=p->front;
	for(int i=0;i<index-1;i++)
	{
		temp=(temp+1)%p->length;
	}
	*target=p->base[temp];
	return 1;
	
}

int LocateElem(Circular_Queue *p, Elemtype target)
{
	if(ListEmpty(p))
	{
		printf("The list is empty!!\n");
		return 0;
	}
	int temp=p->front;
	int index=1;
	while(temp!=p->rear)
	{
		if(p->base[temp]==target)
		{
			return index;
		}
		temp=(temp+1)%p->length;
		index++;
	}
	printf("No such element in the queue!!\n");
	return 0;
}

int push(Circular_Queue *p, Elemtype value)
{
	if((p->rear+1)%p->length==p->front)
	{
		printf("The queue is full\n");
		return 0;
	}
	p->base[p->rear]=value;
	p->rear=(p->rear+1)%p->length;
	return 1;
}

int pop(Circular_Queue *p, Elemtype *value)
{
	if(ListEmpty(p))
	{
		printf("The queue is empty!!\n");
		return 0;
	}
	*value=p->base[p->front];
	p->front=(p->front+1)%p->length;
	return 1;
}

int QueueLength(Circular_Queue *p)
{
	int length=0;
	int temp=p->front;
	while(temp!=p->rear)
	{
		length++;
		temp=(temp+1)%p->length;
	}
	return length; 
}

void show(Circular_Queue *p)
{
	printf("index   value\n");
	printf("FRONT\n");
	int temp=p->front;
	int index=1;
	while(temp!=p->rear)
	{
		printf("  %d       %d\n",index++,p->base[temp]);
		temp=(temp+1)%p->length;
	}
	printf("REAR\n");
}

void clear_list(Circular_Queue *p)
{
	p->rear=p->front;
}




int main(void)
{
	Circular_Queue q;
	InitList(&q);
	int command;
	printf("The stack is initialized!!\n");
	printf("---------------------------------------List-------------------------------------------\n");
	printf("           Command code                                     Function\n");
	printf("                0                                          destroy Queue\n");
	printf("                1                                 tell whether the Queue is empty or not\n");
	printf("                2                         get element of Queue in terms of index from the front\n");
    printf("                3                                  Locate the element in terms of value\n");
    printf("                4                                              push\n");
    printf("                5                                               pop\n");
    printf("                6                                    show the length of the Queue\n");
    printf("                7                                           show the Queue\n");
    printf("                8                                           clear the Queue\n");
    printf("\n\n\n");
    
	while(1)
	{
		printf("Enter corresponding command code:");scanf("%d",&command);getchar();
		switch(command)
		{
			case 0:
				{
					Destroy_list(&q);
					goto label;
				}
			case 1:
				{
					if(ListEmpty(&q))
					{
						printf("The Queue is empty!\n");
					}
					else
					{
						printf("The Queue is not empty!!!\n");
					}
					break;
				}
			case 2:
				{
					int index;
					Elemtype value;
					printf("enter the index, computed from the front of the queue, of the elemnet you want to choose:");scanf("%d",&index);getchar();
					if(GetElem(&q,index,&value))
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
					if(index=LocateElem(&q,value))
					{
						printf("index:%d       value:%d\n",index,value);
					}
					break;
				}
			case 4:
			    {
			    	Elemtype value;
			    	printf("enter the value of the element you want to insert :");scanf("%d",&value);getchar();
			        push(&q,value);
			    	break;
				}
			case 5:
				{
					Elemtype deleted_value;
					if(pop(&q,&deleted_value))
					{
						printf("Deleted value:%d\n",deleted_value);
					}
					break;
				}
			case 6:
				{
					printf("The length of the list:%d\n",QueueLength(&q));
					break;
				}
			case 7:
				{
					show(&q);
					break;
				}
			case 8:
				{
					clear_list(&q);
					break;
				}
			default:printf("enter appropriate command!!\n");
		}
		printf("\n\n");
	}
	
    	
	
label:return 0;
}




