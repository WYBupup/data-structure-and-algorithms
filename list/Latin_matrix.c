#include<stdio.h>
#include<stdlib.h>

typedef struct Element
{
	int value;
	struct Element *next;
}Element, *pointer;

pointer generate();
void show(pointer head);
void print_latin_matrix(pointer head);

pointer generate()
{
	int num;
	printf("enter the matrix's size!!:");scanf("%d",&num);getchar();
	int index=1;
	pointer head=(pointer)malloc(sizeof(Element));
	head->value=index++;
	pointer now = head;
	pointer new_=NULL;
	while(index<=num)
	{
		new_=(pointer)malloc(sizeof(Element));
		new_->value=index++;
		now->next=new_;
		now=new_;
	}
	now->next=head;
	return head;
}

void show(pointer head)
{
	if(head!=NULL)
	{
		int index=1;
		pointer temp=head;
		printf("index             value\n");
		do 
		{
			printf("  %d                 %d\n",index++,temp->value);
			temp=temp->next;
		}while(temp!=head);
	}
	else
	{
		printf("teh circular is empty!!\n");
	}
}

void print_latin_matrix(pointer head)
{
	pointer now=head;
	pointer temp=NULL;
	printf("\n\nthe latin matrix is:\n");
	
	do
	{
		temp=now;
		do
		{
     		if(temp->value>9)
      		{
    			printf(" %d",temp->value);
    		}
    		else
    		{
	    		printf("  %d",temp->value);
	     	}
    		temp=temp->next;
		}while(temp!=now);
		putchar('\n');
		now=now->next; 
	}while(now!=head); 
	
}

int main(void)
{
	
	pointer head=generate();
	show(head);
	print_latin_matrix(head);
	
	
	return 0;
}
