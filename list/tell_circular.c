#include<stdio.h>
#include<stdlib.h>
//tell whether there is a circle in the list
//Implement two kinds of method

typedef struct Element 
{
	int value;
	struct Element *next;
}Element, *pointer;


pointer generate();
void show(pointer head);
int tell_if_circle_1(pointer head);//两个指针pq，p逐渐往前走，q每回都从头开始，若qp所走的步数不同则证明存在问题 
int tell_if_circle_2(pointer head);//两个指针q,p；采用快慢指针。若p可以等于q则证明存在环  more effective



pointer generate()
{
	int index=1;
	pointer new_=NULL,now=NULL,temp=NULL;
	pointer head=(pointer)malloc(sizeof(Element));
	head->value=index++;
	now=head;
	for(int i=0;i<6;i++)
	{
		new_=(pointer)malloc(sizeof(Element));
		new_->value=index++;
		now->next=new_;
		now=new_;
	}
	//now->next=NULL;
	
	temp=now;
	for(int i=0;i<6;i++)
	{
		new_=(pointer)malloc(sizeof(Element));
		new_->value=index++;
		now->next=new_;
		now=new_;
	}
	now->next=temp;
	return head;
	
	
}

void show(pointer head)
{
	int index=1;
	printf("index       value\n");
	while(head!=NULL)
	{
		printf("  %d           %d\n",index++,head->value);
		head=head->next; 
	}
}

int tell_if_circle_1(pointer head)
{
	pointer p=NULL,q=NULL;
	p=q=head;
	int p_step=0,q_step=0;
	while(p!=NULL)
	{
		while(p!=q)
		{
			q=q->next;
			q_step+=1;
		}
		printf("p walks %d steps-----q walks %d steps\n",p_step,q_step);
		printf("p:%p        q:%p\n",p,q);
		if(p_step!=q_step)
		{
			return 1;
		}
		q_step=0;
		q=head;
		p=p->next;
		p_step+=1;
	}
	return 0;
}

int tell_if_circle_2(pointer head)
{
    pointer fast=NULL,slow=NULL;
    fast=slow=head;
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
		if(slow==fast)
		{
			return 1;
		}
	}
	return 0;
} 


int main(void)
{
	pointer head=generate();
	//show(head);
	/*
	if(tell_if_circle_1(head))
	{
		printf("the list have a loop!!\n");
	}
	else
	{
		printf("the list has no loop!!\n");
	}*/
	
	
	if(tell_if_circle_2(head))
	{
		printf("the list have a loop!!\n");
	}
	else
	{
		printf("the list has no loop!!\n");
	}
	
	return 0;
}
