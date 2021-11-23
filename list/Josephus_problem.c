#include<stdio.h>
#include<stdlib.h>
typedef struct person
{
	int number;
	struct person *next;
}person,*pointer;

pointer InitList();
void show(pointer head);
int Length(pointer head);
void Josephus(pointer head,int interval);

pointer InitList()
{
	int num;
	printf("How many people are in the list??:");scanf("%d",&num);getchar();
	if(num<1)
	{
		printf("Please enter the appropriate number of the people!!\n");
		return 0;
	}
	
	int index=1;
	pointer new_=NULL,now=NULL;
	pointer head=(pointer)malloc(sizeof(person));
	head->number=index++;
	now=head;
	
	for(int i=0;i<num-1;i++)
	{
		new_=(pointer)malloc(sizeof(person));
		new_->number=index++;
		now->next=new_;
		now=new_;	
	}
	now->next=head;
	printf("succeessfully generate the list:\n");
	show(head);
	printf("length:%d\n",Length(head));
	return head;
}

int Length(pointer head)
{
	if(head==NULL)
	{
		printf("Empty list!!\n");
		return 0;
	}
	pointer temp=head;
	int counter=0;
	while(1)
	{
		counter++;
		if(temp->next==head)
		{
			break;
		}
		head=head->next;
	}
	return counter;
}

void show(pointer head)
{
	int index=1;
	pointer temp=head;
	while(1)
	{
	     printf("index:%d       id:%d\n",index++,temp->number);
	     if(temp->next==head)
	     {
	     	break;
		 }
	     temp=temp->next;
	}
}

void Josephus(pointer head, int interval)
{
	int count=1;
	int hop=Length(head)%interval;
	if(hop==0)
	{
		printf("No one can escape!!\n");
	}
	else
	{
		pointer temp;
		while(head->next!=head)
		{
			head=head->next;
			count++;
			if(count==hop)
			{
				temp=head->next;
				head->next=temp->next;
				printf("%d->",temp->number);
				free(temp);
				head=head->next;
				count=1;
			}
		}
		printf("%d",head->number);
		free(head);
	}
	
}



int main(void)
{
	pointer head;
	head=InitList();
	printf("--------------------------------------begin the game!!-----------------------------------------------\n");
	Josephus(head,3);
	
	return 0;
}
