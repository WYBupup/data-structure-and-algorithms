#include<stdio.h>
#include<stdlib.h>
//这个代码实现了 链式存储结构的队列
typedef int Elemtype; 
typedef struct Node
{
	Elemtype value;
	struct Node *next;
}Node, *point_node;
typedef struct 
{
	point_node front;
	point_node rear;
}Queue;

 

void InitList(Queue *p);
int ListEmpty(Queue *p); //if empty return 1 else return 0
void Destroy_list(Queue *p);
int GetElem(Queue *p, int index, Elemtype *target);//index is not start from 0;return 0 if fail else return 1  from the front of the Queue
int LocateElem(Queue *p, Elemtype target);//find e in list.succeed:return index+1;else return 0; from the front of the Queue
void push(Queue *p, Elemtype value);//insert new element at the rear of the queue
int pop(Queue *p, Elemtype *value);//succeed return 1 else return 0 get elemtype at the top of the Queue
int QueueLength(Queue *p);
void show(Queue *p);
void clear_list(Queue *p);

void InitList(Queue *p)
{
	p->front=(point_node)malloc(sizeof(Node));
	if(!p->front)
	{
		printf("Fail to allocate the memory!!\n");
		exit(0);
	}
	p->rear=p->front;
	p->front->next=NULL;
}

int ListEmpty(Queue *p)
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

void Destroy_list(Queue *p)
{
	point_node temp;
	while(p->front)
	{
		temp=p->front;
		p->front=p->front->next;
		free(temp);
	}
	p->front=p->rear=NULL;
}

int GetElem(Queue *p, int index, Elemtype *target)
{
	if(QueueLength(p)<index)
	{
		return 0;
	}
	point_node temp=p->front->next;
    for(int i=0; i<index-1;i++)
    {
    	temp=temp->next;
	}
	*target=temp->value;
	return 1;
}

int LocateElem(Queue *p, Elemtype target)
{
	point_node temp=p->front->next;
	int index=1;
	while(temp)
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

void push(Queue *p, Elemtype value)
{
	point_node new_=(point_node)malloc(sizeof(Node));
	new_->value=value;
	new_->next=p->rear->next;
	p->rear->next=new_;
	p->rear=new_;
}

int pop(Queue *p, Elemtype *value)
{
	if(ListEmpty(p))
	{
		return 0;
	}
	point_node temp=p->front->next;
	p->front->next=temp->next;
	if(p->rear==temp)
	{
		p->rear=p->front;
	}
	*value =temp->value;
	free(temp);
	return 1;
	
}

int QueueLength(Queue *p)
{
	int length=0;
	point_node temp=p->front->next;
	while(temp)
	{
		length++;
		temp = temp->next;
	}
	return length;
}

void show(Queue *p)
{
	printf("index       value\n");
	printf("FRONT\n");
	point_node temp=p->front->next;
	int index=1;
	while(temp)
	{
		printf("  %d           %d\n",index++,temp->value);
		temp=temp->next;
	}
	printf("REAR");
}

void clear_list(Queue *p)
{
	point_node temp=p->front->next;
	point_node deleted;
	while(temp)
	{
		deleted = temp;
		temp=temp->next;
		free(deleted);
	}
	p->rear=p->front;
	p->front->next=NULL;
}




int main(void)
{
	Queue q;
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
					else
					{
						printf("out of the range of the queue!!\n");
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
					else
					{
						printf("The stack is empty!!\n");
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



