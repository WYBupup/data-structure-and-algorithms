#include<stdio.h>
#include<stdlib.h>
//此代码运用循环链表实现魔术师发牌问题 
typedef struct card
{
	int value;
	int state;
	struct card *next;
}card,*pointer;

pointer generate(int num);
void assign_card(pointer head,int num);
void show(pointer head);
void destroy_list(pointer head);


pointer move_forward(pointer temp)
{
	//错误点：直接用了while因为不论如何的都要向前走一步 
	do
	{
		temp=temp->next;
	}while(temp->state==1);
	printf("to %p\n",temp);
	return temp;
}

pointer generate(int num)
{
	int count=0;
	pointer head=(pointer)malloc(sizeof(card));
	head->value=0;
	head->state=0;
	pointer now=head;
	pointer new_=NULL;
	count++;
	for(;count<num;count++)
	{
		new_=(pointer)malloc(sizeof(card));
		new_->state=0;
		new_->value=0;
		now->next=new_;
		now=new_;
	}
	now->next=head;
	return head;
	
}

void assign_card(pointer head, int num)
{
	pointer temp=head;
	int count=1;
	int i=1;
	while(i<=num)
	{
		if(count==i)
		{
			temp->value=i++;
			temp->state=1;
			if(i<=num)
			{
				temp=move_forward(temp);
			}
			count=1;
		}
		else
		{
			temp=move_forward(temp);
			count++;
		}
	}
}

void show(pointer head)
{
	if(head!=NULL)
	{
		pointer temp=head;
		int index=1;
		printf("index                      value\n");
		do
		{
			printf("%p             %d\n",temp,temp->value);
			temp=temp->next;
		}while(temp!=head);
	}
	else
	{
		printf("The circular is empty!!\n");
	}
}

void destroy_list(pointer head)
{
	pointer delete_=NULL;
	pointer temp=head;
	do
	{
		delete_=temp;
		temp=temp->next;
		free(delete_);
	}while(temp!=head);
}




int main(void)
{
	pointer head=generate(13);
	show(head);
	printf("\n\n");
	assign_card(head,13);
	show(head);
	destroy_list(head);
	
	return 0;
 } 
