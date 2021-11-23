#include<stdio.h>
#include<stdlib.h>
typedef char Elemtype;
typedef enum {Link, Thread} PointerType; //label the left, right pointer :Link(point to child) Thread(point to previous or later node in midorder sequence)
typedef struct ThBiNode
{
	Elemtype data;
	struct ThBiNode *left, *right;
	PointerType l_tag,r_tag;
}ThBiNode, *ThBiTree;


//Pre-order initial Thread Binary Tree
void PreOrderInitial(ThBiTree *BT)
{
	Elemtype data;
	if(scanf("%c",&data)!=1)
	{
		printf("Error: Please enter the appropriate order(Preorder)!\n");
		exit(0);
	}
	
	
	if(data==' ')
	{
		(*BT)=NULL;
	}
	else
	{
		*BT=(ThBiTree)malloc(sizeof(ThBiNode));
		if((*BT)==NULL)
		{
			printf("Fail to allocate the memory!!\n");
			exit(0);
		}
		(*BT)->data=data;
		(*BT)->l_tag=Link;
		(*BT)->r_tag=Link;
		PreOrderInitial(&((*BT)->left));
		PreOrderInitial(&((*BT)->right)); 
	}
}


//Threadlize with Mid-order
void MidOrderThread(ThBiTree T, ThBiTree *pre) //*pre pointer of pre-tranversed Node; T pointer to the root of BT
{
	if(T)
	{
		MidOrderThread(T->left,pre);
		
		//operation to Node *T
		if(!(T->left))
		{
			T->l_tag=Thread;
			T->left=*pre;
			printf("set %c 's previous node is %c\n",T->data, T->left->data);
		}
		
		
		if(!((*pre)->right))
		{
			(*pre)->r_tag=Thread;
			(*pre)->right=T;
			printf("set %c 's next node is %c\n",(*pre)->data,(*pre)->right->data);
		}
		*pre=T;
		
		MidOrderThread(T->right,pre);
	}
}

void visit(Elemtype data, int level)
{
	printf("level:%d data:%c\n", level, data);
}

//Recursively Tranverse the tree
void MidOrderTranverse(ThBiTree head, ThBiTree T,int level)
{
	if(T->l_tag==Link)
	{
		MidOrderTranverse(head, T->left,level+1);
	}	
	visit(T->data, level);
		
	if(T->r_tag==Link)
	{
		MidOrderTranverse(head,T->right, level+1);
	}
}

//Iteratively tranverse the Thread Binary Tree
void ThreadTranverse(ThBiTree head)
{
	ThBiTree T=head->left;
	if(T!=head)
	{
		while(T->l_tag==Link)
		{
			T=T->left;
		}
		
		visit(T->data,-1);
		
		while(T->right!=head)
		{
		    T=T->right;
			visit(T->data, -1);
		}
	} 
}



int main(void)
{
	//head node left points to root right points to the end node of the Midorder
	ThBiTree head=(ThBiTree)malloc(sizeof(ThBiNode));
	head->data='H';
	head->right=head;
	
	//generate the common Binary Tree with pre-order
	head->l_tag=Link;
	PreOrderInitial(&(head->left));
	
	//Threadize the previous Tree
	ThBiTree pre=head;
	MidOrderThread(head->left, &pre);
	head->r_tag=Thread;
	head->right=pre;
	printf("set %c 's next node is %c\n",head->data, head->right->data);
	pre->r_tag=Thread;
	pre->right=head;
	printf("set %c 's next node is %c\n",pre->data, pre->right->data);
	
	//Tranverse
	printf("\n\n\n\n");
	//MidOrderTranverse(head, head->left, 1);
	ThreadTranverse(head);
	
	return 0;
}



