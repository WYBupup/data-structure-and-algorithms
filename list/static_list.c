#include<stdio.h>
#define MAX 1000

typedef struct
{
	int value;
	int cursor;
}Element, StaticList[MAX];


StaticList L;

void InitList();
int ListEmpty(); //if empty return 1 else return 0
void Clear_list();
int GetElem(int index, int *target);//index is not start from 0;return 0 if fail else return 1
int LocateElem(int target);//find e in list.succeed:return index+1;else return 0;
int ListInsert(int index, int value);//insert new element with value to index(>0),succeed return 1 else return 0;
int ListDelete(int index, int *value);//succeed return 1 else return 0
int ListLength();
void show();
//void union_list(sL1,struct Element *L2);//union L1 and L2 result is L1


void InitList()
{
	//第一个元素的cursor指向备用链表，备用链表末尾元素指向MAX-1；
	//最后一个元素的cursor为静态链表的第一个真正意义上的元素末尾指向0. 
	for(int i=0;i<MAX-1;i++)
	{
		L[i].cursor=i+1;
		L[i].value=0;
	}
	L[MAX-1].cursor=0;
	L[MAX-1].value=0;
}

int ListEmpty()
{
	if(L[MAX-1].cursor==0)
	{
		return 1;
	}
	return 0;
}

void Clear_list()
{
	if(!ListEmpty())
	{
		int ad=L[MAX-1].cursor;
    	int temp_ad;
    	while(ad!=0)
     	{
     		temp_ad=ad;
     		ad=L[ad].cursor;
      		L[temp_ad].value=0;
     		L[temp_ad].cursor=L[0].cursor;
     		L[0].cursor=ad;
     	}
  	}
}

int GetElem(int index, int *target)
{
	int ad=L[MAX-1].cursor;
	for(int i=0;i<index-1;i++)
	{
		if(ad==0)
		{
			break;
		}
		
		ad=L[ad].cursor;
	}
	if(ad==0)
	{
		printf("Out of range of the list");
		return 0;
	}
	else
	{
		*target=L[ad].value;
     	return 1;
	}
}

int LocateElem(int target)
{
	int ad=L[MAX-1].cursor;
	int index=1;
	while(1)
	{
		if(ad==0)
		{
			printf("No such element in the static list!!\n");
		    return 0;
		}
		if(L[ad].value==target)
		{
			break;
		}
		ad=L[ad].cursor;
		index++;
	}
	return index;
}

int ListInsert(int index, int value)
{
	if(L[0].cursor==MAX-1)
	{
		printf("No place for the new element");
		return 0;
	}
	//change the available elememnt list
	int ad_new=L[0].cursor;
	L[0].cursor=L[ad_new].cursor;
	
	/*
	int ad_now,ad_previous;
	ad_previous=MAX-1;
	ad_now=L[MAX-1].cursor; 
	
	for(int i=0;i<index-1;i++)
	{
		ad_previous=ad_now;
		ad_now=L[ad_now].cursor;
		if(ad_now==0&&i!=index-2)
		{
			printf("out of range of the static list!!\n");
			return 0;
		}
	}
	L[ad_previous].cursor=ad_new;
	L[ad_new].cursor=ad_now;
	L[ad_new].value=value;*/
	
	int ad=MAX-1;
	for(int i=0;i<index-1;i++)
	{
		ad=L[ad].cursor;
		if(ad==0)
		{
			break;
		}
	}
	
	if(ad==0)
	{
		printf("out of range of the static list!!\n");
		return 0;
	}
	else
	{
		L[ad_new].value=value;
		L[ad_new].cursor=L[ad].cursor;
		L[ad].cursor=ad_new;
		return 1;	
	}
	
	
	return 1;
}

int ListDelete(int index, int *value)
{
	int ad=MAX-1;
	for(int i =0;i<index-1;i++)
	{
		ad=L[ad].cursor;
		if(L[ad].cursor==0)
		{
			break;
		}
	}
	
	if(L[ad].cursor==0)
	{
		printf("out of the range of the static link");
		return 0;
	}
	else
	{
		int temp=L[ad].cursor;
    	L[ad].cursor=L[temp].cursor;
    	L[temp].value=0;
    	L[temp].cursor=L[0].cursor;
    	L[0].cursor=temp;
    	return 1;
	}
	
}

int ListLength()
{
	int ad = L[MAX-1].cursor;
	int l=0;
	while(ad!=0)
	{
		l++;
		ad=L[ad].cursor;
	}
	return l;
}

void show()
{
	printf("index               value\n");
	int index=1;
    int ad=L[MAX-1].cursor;
    while(ad!=0)
    {
    	printf("  %d                   %d\n",index++,L[ad].value);
    	ad=L[ad].cursor;
	}
}





int main(void)
{
	InitList();
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
					Clear_list();
					goto label;
				}
			case 1:
				{
					int flag=ListEmpty();
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
					if(GetElem(index,&value))
					{
						printf("index:%d       value:%d\n",index,value);
					}
					break;
				}
			case 3:
				{
					int value,index;
					printf("enter the value of the element you want to look for:");scanf("%d",&value);getchar();
					if(index=LocateElem(value))
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
			    	ListInsert(index,value);
			    	break;
				}
			case 5:
				{
					int deleted_value,index;
					printf("Enter the index of the element you want to delete:");scanf("%d",&index);getchar();
					if(ListDelete(index,&deleted_value))
					{
						printf("Deleted index:%d       value:%d\n",index,deleted_value);
					}
					break;
				}
			case 6:
				{
					printf("The length of the list:%d\n",ListLength());
					break;
				}
			case 7:
				{
					show();
					break;
				}
			default:printf("enter appropriate command!!\n");
		}
		printf("\n\n");
	}
	
    	
	
label:return 0;
}
