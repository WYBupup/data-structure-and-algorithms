#include<stdio.h>
#define MAX 128
//child-sibling ½á¹¹ 
typedef int Elemtype;

typedef struct child
{
	int index;
	struct child *next;
}child, *p_child;

typedef struct silbling
{
	int index;
	struct sibling *next;
}sibling, *p_sibling;

typedef struct 
{
	int value;
	p_child child;
	p_sibling sibling;
}Node;

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
