#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 128


//实现利用递归完成二叉树的建立以及二叉树的遍历
//建立和遍历分别包括前序，中序，后序，层序。相应的床前是的输入应满足相应的顺序
//输入中以空格表示NULL

typedef char Elemtype;
typedef struct BiNode
{
	Elemtype data;
	struct BiNode *lchild, *rchild;
} BiNode, *BiTree;

void visit(Elemtype data, int level)
{
	printf("%c is in level %d\n",data,level);
}

//-----------------------二叉树前序遍历以及创建-------------------------------------------
void PreOrderInitial(BiTree *BT)
{
    Elemtype data;
	if(scanf("%c",&data)!=1)
	{
	    printf("Error Please input the data in the proper oreder(preorder)!\n");
		exit(0);	
	}	
	if(data==' ')
	{
		*BT=NULL;
	}
	else
	{
		*BT=(BiTree)malloc(sizeof(BiNode));
		(*BT)->data=data;
		PreOrderInitial(&((*BT)->lchild));
		PreOrderInitial(&((*BT)->rchild));
	}
} 

void PreOrderTransverse(BiTree BT, int level)
{
	if(BT)
	{
		visit(BT->data,level);
		PreOrderTransverse(BT->lchild,level+1);
		PreOrderTransverse(BT->rchild,level+1);
	}
}


//-----------------------二叉树后续序遍历以及创建-------------------------------------------
void PostOrderInitial(BiTree *BT,char datas[], int *counter)
{
	if(*counter<0)
	{
		printf("Error Please enter the data in the proper order!(Post order)!!\n");
		exit(0);
	}
	Elemtype data=datas[*counter];
	(*counter)--;
	if(data==' ')
	{
		*BT=NULL;
	}
	else
	{
		*BT=(BiTree)malloc(sizeof(BiNode));
		(*BT)->data=data;
		PostOrderInitial(&((*BT)->rchild),datas,counter);
		PostOrderInitial(&((*BT)->lchild),datas,counter);
	}
}

void PostOrderTranverse(BiTree BT,int level)
{
	if(BT)
	{
		
     	PostOrderTranverse(BT->lchild,level+1);
        PostOrderTranverse(BT->rchild,level+1);
		visit(BT->data,level);
	}
}

//-----------------------二叉树中续序遍历以及创建-------------------------------------------
//扩展中序序列为无效序列，无法尤其构造唯一的二叉树 

void MidOrdertranverse(BiTree BT, int level)
{
	if(BT)
	{
		MidOrdertranverse(BT->lchild,level+1);
		visit(BT->data,level);
		MidOrdertranverse(BT->rchild,level+1);
	}
}


int main(void)
{
	BiTree BT=NULL;
	
	//Pre-order
	/*
	PreOrderInitial(&BT);
	PreOrderTransverse(BT,1);*/
	
	//Post-order
	char datas[MAX];
	fgets(datas,MAX,stdin);datas[strlen(datas)-1]='\0';
	printf("The datas youhave input:%s\n",datas);
	int counter=strlen(datas)-1;
	PostOrderInitial(&BT,datas,&counter);
	//PostOrderTranverse(BT,1);
	
    
    //Midorder
    
    MidOrdertranverse(BT,1);
	
	//level-order 
	
	
	return 0;
}
