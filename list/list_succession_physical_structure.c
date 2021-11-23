#include <stdio.h>
#include<stdlib.h>
#define MAX 1024
// list created by 6
sequential structure
typedef int Eletype;
typedef struct 
{
	Eletype data[MAX];
	int length;
} SqList;

void InitList(SqList **L);
int ListEmpty(SqList *L); //if empty return 1 else return 0

void Clear_List(SqList *L);
int GetElem(SqList *L, int index, int *target);//index is not start from 0;return 0 if fail else return 1
int LocateElem(SqList *L, int target);//find e in list.succeed:return index+1;else return 0;
int ListInsert(SqList *L, int index, int value);//insert new element with value to index(>0),succeed return 1 else return 0;
int ListDelete(SqList *L, int index, int *value);//succeed return 1 else return 0
int ListLength(SqList *L);
void show(SqList *L);
void union_list(SqList *L1,SqList *L2);//union L1 and L2 result is L1


void InitList(SqList **L)
{
	*L=(SqList *)malloc(sizeof(SqList));
	(*L)->length=0; 
}

int ListEmpty(SqList *L)
{
	if(L->length==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Clear_List(SqList *L)
{
	free(L);
	printf("Clear the SqList!!\n");
}

//T(n)=o(1)
int GetElem(SqList *L, int index, int *target)
{
	if(index>L->length || index<1)
	{
		printf("out of the range of SqList!!\n");
		return 0;
	}
	*target = L->data[index-1];
	return 1;
}

//T(n)=o(n)
int LocateElem(SqList *L, int target)
{
	for (int i=0;i<L->length;i++)
	{
		if(L->data[i]==target)
		{
			return i+1;
		}
	}
	printf("No such element in the SqList!!\n");
	return 0;
}


// T(n)=o(n)
int ListInsert(SqList *L, int index, int value)
{
	if(index>L->length+1 || index<1 || L->length>=MAX)
	{
		printf("Fail to insert element!!\n");
		return 0;
	}
	if(index<=L->length)
	{
		for(int i=L->length-1;i>=index-1;i--)
		{
			L->data[i+1]=L->data[i];
		}
	}
	L->data[index-1]=value;
	L->length++;
	printf("insert: index:%d    value:%d",index,L->data[index-1]);
	return 1;
}


//T(n)=o(n)
int ListDelete(SqList *L, int index, int *value)
{
	if(index<1 || index>L->length)
	{
		printf("Fail to delete element!!\n");
		return 0;
	}
	*value=L->data[index-1];
	for(int i=index-1;i<=((L->length)-2);i++)
	{
		L->data[i]=L->data[i+1];
	}
	L->length--;
	return 1;
}

int ListLength(SqList *L)
{
	return L->length;
}

void show(SqList *L)
{
	printf("index                 value\n");
	for(int i=0; i<L->length;i++)
	{
		printf("  %d                      %d\n",i+1,L->data[i]);
	}
	putchar('\n');
}

void union_list(SqList *L1,SqList *L2)
{
	for (int i=0; i<L2->length;i++)
	{
		if(!LocateElem(L1,L2->data[i]))
		{
			ListInsert(L1,L1->length+1,L2->data[i]);
		}
	}
}



int main(void)
{
	SqList *L=NULL;
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
    printf("\n\n\n");
    
	while(1)
	{
		printf("Enter corresponding command code:");scanf("%d",&command);getchar();
		switch(command)
		{
			case 0:
				{
					Clear_List(L);
					goto label;
				}
			case 1:
				{
					if(ListEmpty(L))
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
						printf("index:%d       value:%d\n",index,L->data[index-1]);
					}
					break;
				}
			case 4:
			    {
			    	int value,index;
					printf("enter the index of the elemnet you want to insert:");scanf("%d",&index);getchar();
			    	printf("enter the value of the element you want to insert :");scanf("%d",&value);getchar();
			    	ListInsert(L,index,value);
			    	break;
				}
			case 5:
				{
					int deleted_value,index;
					printf("Enter the index of the element you want to delete:");scanf("%d",&index);getchar();
					if(ListDelete(L,index,&deleted_value))
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
			default:printf("enter appropriate command!!\n");
		}
		printf("\n\n");
	}
	
    	
	
label:return 0;
}


















