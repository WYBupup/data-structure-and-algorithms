#include<stdio.h>
#include<stdlib.h>
//这个代码实现了circular list 有头节点 
struct Element
{
	struct Element *next;
	int value;
};


int InitList(struct Element *head,struct Element **rear);//succeed return 1;else return 0;
int ListEmpty(struct Element *head); //if empty return 1 else return 0
void Clear_list(struct Element *head,struct Element *rear);
int GetElem(struct Element *head, struct Element *rear,int index, int *target);//index is not start from 0;return 0 if fail else return 1
int LocateElem(struct Element *head, int target);//find e in list.succeed:return index+1;else return 0;
int ListInsert(struct Element **head, struct Element **rear, int index, int value);//insert new element with value to index(>0),succeed return 1 else return 0;
int ListDelete(struct Element **head, struct Element **rear, int index, int *value);//succeed return 1 else return 0
int ListLength(struct Element *head);
void show(struct Element *head);
//void union_list(struct Element **L1,struct Element *L2);//union L1 and L2 result is L1
int find_mid_value(struct Element *head,int *value,int *index);//successed return 1;else return 0;
//void random_generate(struct Element **head,int num);

int InitList(struct Element *head, struct Element **rear)
{
	if(!ListEmpty(head))
	{
		printf("The List has been initialized!!\n");
		return 0;
	}
	
	int num,value,i=1;
	struct Element *new_=NULL;
	
	printf("How many elements do you want to initialize?:");scanf("%d",&num);getchar();
	if(num<=0)
	{
		printf("please enter the initialized number bigger than 0!!!\n");
		return 0;
	}
	
	//tail insert
	//No.1 Element 
	/*
	printf("enter the No.%d element's value:",i++);scanf("%d",&value);getchar();
	new_=(struct Element *)malloc(sizeof(struct Element));
	new_->value=value;
	new_->next=(*rear)->next;
	head->next=new_;
	*rear=new_;*/
	
	//Other element 
	while(i<=num)
	{
		printf("enter the No.%d element's value:",i++);scanf("%d",&value);getchar();
		new_=(struct Element *)malloc(sizeof(struct Element));
		new_->value=value;
		new_->next=(*rear)->next;
		(*rear)->next=new_;
		*rear=new_;
	}
	return 1;
}

int ListEmpty(struct Element *head)
{
	if(head->next==head)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Clear_list(struct Element *head,struct Element *rear)
{
	struct Element *temp;
	while(1)
	{
		temp=head;
		if(temp==rear)
		{
			free(temp);
			break;
		}
		else
		{
			head=head->next;
			free(temp);
		}
	}
}

int GetElem(struct Element *head, struct Element *rear,int index, int *target)
{
	if(index<1 || index>ListLength(head))
	{
		printf("out of range of the circular list!!\n");
		return 0;
	}
	
	head=head->next;
	for(int i=0;i<index-1;i++)
	{
		head=head->next;
	}
	*target=head->value;
	return 1;
}

int LocateElem(struct Element *head, int target)
{
	struct Element *temp=head->next;
	int index=1;
	while(temp!=head)
	{
		if(temp->value==target)
		{
			break;
		}
		temp=temp->next;
		index++;
	}
	if(temp==head)
	{
	    return 0;
	}
	else
	{
		return index;
	}
}

int ListInsert(struct Element **head, struct Element **rear, int index, int value)
{
	if(index<1 || index>ListLength(*head)+1)
	{
		printf("out of range of the circular list!!\n");
		return 0;
	}
	
	struct Element *new_=(struct Element *)malloc(sizeof(struct Element));
	
	head=&((*head)->next);
	for(int i=0;i<index-1;i++)
	{
		head=&((*head)->next);
	}
	new_->next=*head;
	new_->value=value;
	if(*head==(*rear)->next)
	{
		*rear=new_;
	}
	*head=new_;
	
	
	 printf("successfully insert %d to index %d\n",value,index);
	 return 1;
}

int ListDelete(struct Element **head, struct Element **rear,int index, int *value)
{
	if(index>ListLength(*head) || index<1)
	{
		printf("out of range of the circular list!!!\n");
		return 0;
	}
	struct Element *temp;
	for (int i=0;i<index-1;i++)
	{
		head=&(*head)->next;
	}
	
	temp=(*head)->next;
	if(temp==*rear)
	{
		*rear=*head;
	}
	(*head)->next=temp->next;
	*value=temp->value;
	free(temp);
	return 1;
	
}

int ListLength(struct Element *head)
{
	struct Element *temp=head->next;
	int num=0;
	while(temp!=head)
	{
		temp=temp->next;
		num++;
	}
	return num;
}

void show(struct Element *head)
{
	struct Element *temp=head->next;
	int index=1;
	printf("index              value\n");
	while(temp!=head)
	{
		printf("  %d                  %d\n",index++,temp->value);
		temp=temp->next;
	}
}

int find_mid_value(struct Element *head,int *value,int *index)
{
	if(ListEmpty(head))
	{
		printf("the list is empty!!\n");
		return 0;
	}
	int id=1;
	struct Element *fast,*slow;
	fast=slow=head->next;
	while(fast->next!=head)
	{
		if(fast->next->next!=head)
		{
			fast=fast->next->next;
		}
		else
		{
			fast=fast->next;
		}
		slow=slow->next;
		id++;
	}
	*index=id;
	*value=slow->value;
	
	return 1;
}



int main(void)
{
	struct Element *head,*rear;
	head=(struct Element *)malloc(sizeof(struct Element));
	head->value=0;
	head->next=head;
	rear=head;
	InitList(head,&rear);
	int command;
	printf("The list is initialized!!\n");
	printf("---------------------------------------List-------------------------------------------\n");
	printf("           Command code                                     Function\n");
	printf("                0                                          Empty List\n");
	printf("                1                                 tell whether the list is empty or not\n");
	printf("                2                                  get element of list in terms of index\n");
    printf("                3                                  Locate the element in terms of value\n");
    printf("                4                                   Insert New element to the list\n");
    printf("                5                                delete particular element interms of index\n");
    printf("                6                                    show the length of the list\n");
    printf("                7                                           show the list\n");
    printf("                8                                       generate random list\n");
    printf("                9                                         find middle value\n");
    printf("\n\n\n");
    
	while(1)
	{
		printf("Enter corresponding command code:");scanf("%d",&command);getchar();
		switch(command)
		{
			case 0:
				{
					Clear_list(head,rear);
					goto label;
				}
			case 1:
				{
					if(ListEmpty(head))
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
					int index,value;
					printf("enter the index of the element you want to choose:");scanf("%d",&index);getchar();
					if(GetElem(head,rear,index,&value))
					{
						printf("index:%d       value:%d\n",index,value);
					}
					break;
				}
			case 3:
				{
					int value,index;
					printf("enter the value of the element you want to look for:");scanf("%d",&value);getchar();
					if(index=LocateElem(head,value))
					{
						printf("index:%d       value:%d\n",index,value);
					}
					else
					{
						printf("No such element in the list!\n");
					}
					break;
				}
			case 4:
			    {
			    	int value,index;
					printf("enter the index of the elemnet you want to insert:");scanf("%d",&index);getchar();
			    	printf("enter the value of the element you want to insert :");scanf("%d",&value);getchar();
			    	ListInsert(&head,&rear,index,value);
			    	break;
				}
			case 5:
				{
					int deleted_value,index;
					printf("Enter the index of the element you want to delete:");scanf("%d",&index);getchar();
					if(ListDelete(&head,&rear,index,&deleted_value))
					{
						printf("Deleted index:%d       value:%d\n",index,deleted_value);
					}
					break;
				}
			case 6:
				{
					printf("The length of the list:%d\n",ListLength(head));
					break;
				}
			case 7:
				{
					show(head);
					break;
				}
			case 8:
				{
					/*
					int num;
					printf("enter the length of the list:");scanf("%d",&num);getchar();
					random_generate(&L,num);*/
					break;
				}
			case 9:
				{
					int index,value;
					if(find_mid_value(head,&value,&index))
					{
						printf("middle value: index:%d        value:%d\n",index,value);
					}
					break;
				}
			default:printf("enter appropriate command!!\n");
		}
		printf("\n\n");
	}
	
    	
	
label:return 0;
}
