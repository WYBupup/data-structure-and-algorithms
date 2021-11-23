#include<stdio.h>
#include<stdlib.h>

typedef struct Element 
{
	int value;
	struct Element *next;
}Element, *pointer;


pointer generate();//返回指向尾节点的指针 
void show(pointer rear);
pointer connect(pointer first, pointer second);

pointer generate()
{
    int num;
    int value;
    int index=1;
	printf("How many elements are there in the circular list?:");scanf("%d",&num);getchar();
	pointer head=(pointer)malloc(sizeof(Element));
	pointer rear=head;
	printf("Enter the No.%d element's value:",index++);scanf("%d",&value);getchar();
	rear->value=value;
	
	pointer new_=NULL;
	for(;index<=num;index++)
	{
		new_=(pointer)malloc(sizeof(Element));
     	printf("Enter the No.%d element's value:",index);scanf("%d",&value);getchar();
    	new_->value=value;
    	rear->next=new_;
    	rear=new_;
	}
	rear->next=head;
	return rear;	
}

void show(pointer rear)
{
	pointer head=rear->next;
	pointer temp=head;
	printf("index          value\n");
	int index=0;
	do
	{
		printf("  %d               %d\n",++index,temp->value);
		temp=temp->next;
	}while(temp!=head);
}

pointer connect(pointer first, pointer second)
{
	pointer temp=first->next;
	first->next=second->next;
	second->next=temp;
	return second;
}


int main(void)
{
	pointer rear_1=generate();
	pointer rear_2=generate();
	printf("rear_1:\n");show(rear_1);
	printf("\n\n");
	printf("rear_2:\n");show(rear_2);
	printf("\n\n");
	
	pointer connected=connect(rear_1,rear_2);
	printf("connected:\n");show(connected);
	printf("\n\n");
	return 0;
}
