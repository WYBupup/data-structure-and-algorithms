#include<stdio.h>
#include<stdlib.h>
#include"Statistical_sort.c"
#define MAX 128

//这部分包括优先队列的操作
//根据输入字符串的统计信息生成优先队列
//队列的初始化、push、pop、按序插入等操作 



typedef struct BiNode
{
	Freq_Char freq_char;
	struct BiNode *lchild, *rchild;
}BiNode, *BiTree;

typedef struct QNode
{
	BiTree bitree;
	struct QNode *next;
}QNode, *p_QNode;

typedef struct 
{
	p_QNode front;
	p_QNode rear;
	int length;
}Priority_Queue;


void Init_Queue(Priority_Queue *q);
void Genertae_Priority_Queue(Freq_List list, Priority_Queue *q);
void tranverse_queue(Priority_Queue q);
void Generate_Priority_Queue(Freq_List list, Priority_Queue *q);
BiTree Queue_pop(Priority_Queue *q);


Freq_List Compute_ch_freq(char *str);
void Tranverse_freq_list(Freq_List list);
void Sort_freq_list(Freq_List *list);
void Insert_Queue(Priority_Queue *q, BiTree tree);



void Init_Queue(Priority_Queue *q)
{
	q->front=(p_QNode)malloc(sizeof(QNode));
	q->front->bitree=NULL;
	q->front->next=NULL;
	
	q->rear=q->front;
	q->length=0;
}

void tranverse_queue(Priority_Queue q)
{
	p_QNode temp=q.front->next;
	
	printf("length:%d\nIndex    Character          Frequency\n",q.length);
	int index=1;
	while(temp!=NULL)
	{
		if (index>9)
		{
			printf(" %d          %c                   %d\n",index++,temp->bitree->freq_char.data, temp->bitree->freq_char.frequency);
		}
		else
		{
			printf("  %d          %c                   %d\n",index++,temp->bitree->freq_char.data, temp->bitree->freq_char.frequency);
		}
		temp=temp->next;
	}
	printf("\n\n");
}

void Queue_push(Priority_Queue *q, Freq_Char freq_char)
{
	BiTree tree_temp=(BiTree)malloc(sizeof(BiNode));
	tree_temp->freq_char=freq_char;
	tree_temp->lchild=NULL;
	tree_temp->rchild=NULL;
	
	p_QNode p_node_temp=malloc(sizeof(QNode));
	p_node_temp->bitree=tree_temp;
	p_node_temp->next=q->rear->next;
	
	q->rear->next=p_node_temp;
	q->rear=p_node_temp;
	
	q->length++;
}

BiTree Queue_pop(Priority_Queue *q)
{
	if(q->length==0)
	{
		printf("The Queue is empty!!\n");
		exit(0);
	}
	p_QNode temp=q->front->next;
	q->front->next=temp->next;
	if(temp==q->rear)
	{
		q->rear=q->front; 
	}
	/*
	BiTree tree=temp->bitree;
	free(temp);*/
	q->length--;
	return temp->bitree;
}



void Generate_Priority_Queue(Freq_List list, Priority_Queue *q)
{
    for (int i=0;i<list.length;i++)
    {
    	Queue_push(q,list.list[i]);
	}
}

void Insert_Queue(Priority_Queue *q, BiTree tree)
{
	int frequency=tree->freq_char.frequency;
	p_QNode temp=q->front;
	while(temp->next!=NULL)
	{
		if(temp->next->bitree->freq_char.frequency>=frequency)
		{
			break;
		}
		temp=temp->next;
	}
	
	p_QNode new_=(p_QNode)malloc(sizeof(QNode));
	new_->bitree=tree;
	new_->next=temp->next;
	
	if(temp==q->rear)
	{
		q->rear=new_;
	}
	temp->next=new_;
	
	q->length++;

}

#if 0
int main(void)
{
	char str[] = "abdgshakkadhausiajdnajsjahsan";
	Freq_List list=Compute_ch_freq(str);
	Tranverse_freq_list(list);
	Sort_freq_list(&list);
	Tranverse_freq_list(list);
	
	Priority_Queue q;
	Init_Queue(&q);
	Generate_Priority_Queue(list, &q);
	tranverse_queue(q);
	
	return 0;
}
#endif
