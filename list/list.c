#include <stdio.h>
#include<stdlib.h>
#include<time.h>
//No implementation of memory pool
//这个代码实现了利用快慢指针来进行查找中间值 
struct Element
{
	struct Element *next;
	int value;
};




void InitList(struct Element **L);
int ListEmpty(struct Element *L); //if empty return 1 else return 0
void Clear_list(struct Element **L);
int GetElem(struct Element *L, int index, int *target);//index is not start from 0;return 0 if fail else return 1
int LocateElem(struct Element *L, int target);//find e in list.succeed:return index+1;else return 0;
int ListInsert(struct Element **L, int index, int value);//insert new element with value to index(>0),succeed return 1 else return 0;
int ListDelete(struct Element **L, int index, int *value);//succeed return 1 else return 0
int ListLength(struct Element *L);
void show(struct Element *L);
void union_list(struct Element **L1,struct Element *L2);//union L1 and L2 result is L1
int find_mid_value(struct Element *head,int *value,int *index);//successed return 1;else return 0;
void random_generate(struct Element **head,int num);



void union_list(struct Element **L1,struct Element *L2)//under authentication!!!
{
	while(L2!=NULL)
	{
        if(LocateElem(*L1,L2->value)==0)
        {
        	ListInsert(L1,ListLength(*L1)+1,L2->value);
		}
		L2=L2->next; 
	}
}

void InitList(struct Element **L)
{
	if(*L==NULL)
	{
		printf("The List has been initialized!!\n");
	}
	else
	{
	    *L=NULL;
	}
}

int ListEmpty(struct Element *L)
{
	if(L==NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
} 
//T(n)=o(n)
void Clear_list(struct Element **L)
{
	if(*L!=NULL)
	{
		struct Element *L_=*L;
		struct Element *temp=NULL;
		while(L_!=NULL)
		{ 
			temp=L_;
			L_=L_->next;
			free(temp);
		}
		*L=NULL;
	}
}
//T(n)=o(n)
int GetElem(struct Element *L, int index, int *target)
{
	/*
	if(index>ListLength(L))
	{
		printf("Out of range of the list!!\n");
		return 0;
	}
	*/
	
	for(int i=0;i<index-1;i++)
	{
		L=L->next;
		if(L==NULL)
		{
			printf("Out of range of the list!!\n");
		    return 0;
		}
	}
	*target=L->value;
	return 1;
}
//T(n)=o(n)
int LocateElem(struct Element *L, int target)
{
	for(int index=0;L!=NULL;index++,L=L->next)
	{
		if(L->value==target)
		{
			return index+1;
		}
	}
	printf("No element with value of %d in list!!\n",target);
	return 0;
}
//T(n)=o(n) 相比于顺序结构，当连续插入时第一次插入o(n) 之后都尉o(1) 
int ListInsert(struct Element **L, int index, int value)
{
	/*
	if(index>ListLength(*L)+1)
	{
		printf("Out of range of array!!\n");
		return 0;
	}
	*/
	struct Element *new_e=(struct Element *)malloc(sizeof(struct Element));
	new_e->value=value;
	
	for(int i=0;i<index-1;i++)
	{
		L=&((*L)->next);
		if(*L==NULL && i<index-2)
		{
			printf("Out of range of array!!\n");
		    return 0;
		}
	}
	struct Element *temp=*L;
	*L=new_e;
	new_e->next=temp;
	printf("succcessfully insert %d to index %d\n",value,index);
	return 1;
}
//T(n)=o(n)  相比于顺序结构，当连续插入时第一次插入o(n) 之后都尉o(1) 
int ListDelete(struct Element **L, int index, int *value)
{
	/*
	if(index>ListLength(*L))
	{
		printf("Out of range of the list!!\n");
		return 0;
	}*/
	
	for(int i=0;i<index-1;i++)
	{
		L=&((*L)->next);
		if(*L==NULL)
		{
			printf("Out of range of array!!\n");
		    return 0;
		}
	}
	
	struct Element *temp=*L;
	*L=(*L)->next;
	*value=temp->value;
	free(temp);
	return 1;
    
}

int ListLength(struct Element *L)
{
	int length=0;
	while(L!=NULL)
	{
		L=L->next;
		length++;
	}
	return length;
}
//T(n)=  
void show(struct Element *L)
{
	int index=1;
	printf("index                    value\n");
	while(L!=NULL)
	{
		printf("  %d                      %d\n",index,L->value);
		L=L->next;
		index++;
	}
	putchar('\n');
}

void random_generate(struct Element **head,int num)
{
	time_t t;
	time(&t);
	srand((unsigned int)t);
	
	for(int i=0;i<num;i++)
	{
		ListInsert(head,1,rand()%100);
	}
	printf("successfully insert %d random numbers to the List!!\n",num);
}

int find_mid_value(struct Element *head, int *value, int *index)
{
	if(ListEmpty(head))
	{
		printf("List is empty!!\n");
		return 0;
	}
	struct Element *fast=head;
	struct Element *slow=head;
	int id=1;
	
	while(fast->next!=NULL)
	{
		if(fast->next->next!=NULL)
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
	struct Element *L;
	InitList(&L);
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
					Clear_list(&L);
					goto label;
				}
			case 1:
				{
					int flag=ListEmpty(L);
					if(flag)
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
					printf("enter the index of the elemnet you want to choose:");scanf("%d",&index);getchar();
					if(GetElem(L,index,&value))
					{
						printf("index:%d       value:%d\n",index,value);
					}
					break;
				}
			case 3:
				{
					int value,index;
					printf("enter the value of the element you want to look for:");scanf("%d",&value);getchar();
					if(index=LocateElem(L,value))
					{
						printf("index:%d       value:%d\n",index,value);
					}
					break;
				}
			case 4:
			    {
			    	int value,index;
					printf("enter the index of the elemnet you want to insert:");scanf("%d",&index);getchar();
					if(index>ListLength(L)+1)
					{
						printf("Out of range of the list!!\n");
						break;
					}
			    	printf("enter the value of the element you want to insert :");scanf("%d",&value);getchar();
			    	ListInsert(&L,index,value);
			    	break;
				}
			case 5:
				{
					int deleted_value,index;
					printf("Enter the index of the element you want to delete:");scanf("%d",&index);getchar();
					if(ListDelete(&L,index,&deleted_value))
					{
						printf("Deleted index:%d       value:%d\n",index,deleted_value);
					}
					break;
				}
			case 6:
				{
					printf("The length of the list:%d\n",ListLength(L));
					break;
				}
			case 7:
				{
					show(L);
					break;
				}
			case 8:
				{
					int num;
					printf("enter the length of the list:");scanf("%d",&num);getchar();
					random_generate(&L,num);
					break;
				}
			case 9:
				{
					int index,value;
					if(find_mid_value(L,&value,&index))
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
