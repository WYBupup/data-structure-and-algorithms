#include<stdio.h>
#include<stdlib.h>
#include"Priority_Queue.c"
#include<string.h>

//这部分包括Huffman树的生成
//Huffman表的生成
//根据huffman表对字符串进行编码
//根据Huffman树对编码进行解码 

typedef struct 
{
	char data;
	char code[MAX];
}huffman_table_elem;


typedef struct
{
	huffman_table_elem table[MAX];
	int length;
}Huffman_table;

void Init_Queue(Priority_Queue *q);
void Genertae_Priority_Queue(Freq_List list, Priority_Queue *q);
void tranverse_queue(Priority_Queue q);
void Generate_Priority_Queue(Freq_List list, Priority_Queue *q);
void Insert_Queue(Priority_Queue *q, BiTree tree);


Freq_List Compute_ch_freq(char *str);
void Tranverse_freq_list(Freq_List list);
void Sort_freq_list(Freq_List *list);
BiTree Queue_pop(Priority_Queue *q);

BiTree generate_Huffman_Tree(Priority_Queue *q);
void generate_huffman_table(Huffman_table *table, BiTree tree, char *code);
void Huffman_decoding(char *decoded_str, BiTree tree, char *encoded_str);
void Huffman_encoding(char *encoded_str, char *str, Huffman_table table);


BiTree generate_Huffman_Tree(Priority_Queue *q)
{
	
	if(q->length==0)
	{
		printf("Priority Queue is empty!!\n");
		exit(0);
	}
	
	
	while(q->length>1)
	{
		BiTree temp_1=Queue_pop(q);
	    BiTree temp_2=Queue_pop(q);
	    BiTree tree=(BiTree)malloc(sizeof(BiNode));
	    tree->freq_char.frequency=temp_1->freq_char.frequency+temp_2->freq_char.frequency;
	    tree->freq_char.data='*';
	    tree->lchild=temp_1;
	    tree->rchild=temp_2;
	    
	    Insert_Queue(q, tree);
	}
	return q->front->next->bitree;
}



void generate_huffman_table(Huffman_table *table, BiTree tree, char *code)
{
	//pre-order tranverse huffman tree
	if(tree)
	{
		
		if(tree->lchild==NULL && tree->rchild==NULL)
		{
			table->table[table->length].data=tree->freq_char.data;
			strcpy(table->table[table->length].code,code);
			table->length++;
		}
		
		int index=strlen(code);
		
		code[index]='0';
		code[index+1]='\0';
		generate_huffman_table(table, tree->lchild,code);
		
		code[index]='1';
		code[index+1]='\0';
		generate_huffman_table(table, tree->rchild,code);
	}
}


void Huffman_decoding(char *decoded_str, BiTree tree, char *encoded_str)
{
	int index=0;//index of decoded string
	BiTree temp=tree;
	
	int i=0;//index of encoded string
	while(1)
	{
		if(temp==NULL)
		{
			printf("ERROR!!!NULL Huffman node\n");
			exit(0);
		}
		
		if(temp->lchild==NULL  && temp->rchild==NULL)
		{
			decoded_str[index++]=temp->freq_char.data;
			temp=tree;
			
			//终止条件 
			if(encoded_str[i]=='\0')
			{
				break;
			}
		}
		else
		{
			if(encoded_str[i]=='0')
			{
				temp=temp->lchild;
			}
			else if(encoded_str[i]=='1')
			{
				temp=temp->rchild;
			}
			else
			{
				printf("ERROR!!Encoded string contains character other than 0 and 1");
				exit(0);
			}
			i++;
		}
		
	}
	decoded_str[index]='\0';
}

void Huffman_encoding(char *encoded_str, char *str, Huffman_table table)
{
	int index=0;
	for(int i=0; str[i]!='\0';i++)
	{
		int j;
		for(j=0;j<table.length;j++)
		{
			if (table.table[j].data==str[i])
			{
				char *temp=table.table[j].code;
				for(int k=0;temp[k]!='\0';k++)
				{
					encoded_str[index++]=temp[k];
				}
				break;
			}
		}
		if(j==table.length)
		{
			printf("Error!Cant find corresponding code for %c in huffman table!\n",str[i]);
			exit(0);
		}
	}
	encoded_str[index]='\0';
}

 



int main(void)
{
	char str[] = "abdgshakkadhausiajdnajsjahsan";
	printf("Str:\n%s\n\n",str);
	
	//statistical process for string
	Freq_List list=Compute_ch_freq(str);
	Sort_freq_list(&list);
	
	//generate priority queue
	Priority_Queue q;
	Init_Queue(&q);
	Generate_Priority_Queue(list, &q);
	
	//generate huffman tree
	BiTree tree=generate_Huffman_Tree(&q);
	
	//generate huffman table
	Huffman_table table;
	table.length=0;
	char code[MAX];
	code[0]='\0';
	generate_huffman_table(&table, tree, code);
	
	
	//tranverse huffman table
	printf("Huffman table\n");
	for (int i=0;i<table.length;i++)
	{
		printf("%c     %s\n",table.table[i].data,table.table[i].code);
	}
	printf("\n\n");
	
	
	//encode string
	printf("encoding....\n");
	char encoding[1024];
    Huffman_encoding(encoding, str, table);
	printf("%s\n\n",encoding);
	
	//decoding
	printf("decoding.....\n");
	char decoding[MAX];
	Huffman_decoding(decoding, tree, encoding);
	printf("%s\n",decoding);
	printf("%s",str);

	

	return 0;
}
