#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Element
{
	int value;
	struct Element *next;
}Element, *Link;

void entire_generate_head(Link *head,int num);
void entire_generate_tail(Link *head,int num);
void show(Link l);

void show(Link l)
{
	printf("index                  value\n");
	int index=1;
	l=l->next;
	while(l!=NULL)
	{
		printf("  %d                       %d\n",index++,l->value);
		l=l->next;
	}
}


void entire_generate_head(Link *head, int num)
{
	time_t t;
	time(&t);
	srand((unsigned int)t);
	
	*head=(Link)malloc(sizeof(Element));
	(*head)->next=NULL;
	
	
	for(int i=0;i<num;i++)
	{
		Link p_new=(Link)malloc(sizeof(Element));
		p_new->value=rand()%100+1;
		p_new->next=(*head)->next;
		(*head)->next=p_new; 
	}
}


void entire_generate_tail(Link *head,int num)
{
	time_t t;
	time(&t);
	srand((unsigned int)t);
	
	
	Link r=NULL;
	*head=(Link)malloc(sizeof(Element));
	r=*head;
	
	for(int i=0;i<num;i++)
	{
		Link p=(Link)malloc(sizeof(Element));
		p->value=rand()%100+1;
		r->next=p;
		r=p;
	}
	r->next=NULL;
}


int main(void)
{
	Link head=NULL;
	/*
	entire_generate_head(&head,20);
	show(head);
	*/
	
	entire_generate_tail(&head,20);
	show(head);
	
	
	
	return 0;
}
