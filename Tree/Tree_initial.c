#include<stdio.h>
//����˫�׺��ӷ������� 
#define MAX 128
typedef int Elemtype;

//���ӽڵ� 
typedef struct child
{
	int index;
	struct child *next;
}child, *p_child;

//NODE 
typedef struct 
{
	Elemtype value;
	int parent;
	p_child children;
}Node;

//Tree
typedef struct 
{
	int root; 
	int length;
	Node nodes[MAX];
}Tree;
 

int main(void)
{
	
	
	return 0;
}
