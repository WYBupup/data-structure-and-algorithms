#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 128


//ʵ�����õݹ���ɶ������Ľ����Լ��������ı���
//�����ͱ����ֱ����ǰ�����򣬺��򣬲�����Ӧ�Ĵ�ǰ�ǵ�����Ӧ������Ӧ��˳��
//�������Կո��ʾNULL

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

//-----------------------������ǰ������Լ�����-------------------------------------------
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


//-----------------------����������������Լ�����-------------------------------------------
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

//-----------------------����������������Լ�����-------------------------------------------
//��չ��������Ϊ��Ч���У��޷����乹��Ψһ�Ķ����� 

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
