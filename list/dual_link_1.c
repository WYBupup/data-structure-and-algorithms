#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 128
//这个代码实现了用户输入整正数，向前移动正数位，再开始 正向遍历链表
//当输入负数时。向后移动附属绝对值位之后，再反向遍历链表
//实现了Vigenere code and decode 详细见小甲鱼 数据结构与算法 
 

typedef struct Element
{
	char value;
	struct Element *next;
	struct Element *prior;
}Element, *pointer;

typedef struct 
{
	char str[MAX];
	int code[MAX];
}Vigenere;

pointer generate();
void show(int orientation, pointer head);//orientation=1 正向; orientation=-1 反向
char get_char(int loc, int skip, pointer head);
Vigenere generate_Vigenere_couple(char *str);
void get_str_coded(char *str_coded,Vigenere char_code,pointer head);
void get_str_decoded(char *str_decoded, char *str_coded, Vigenere char_coded,pointer head);
 
pointer generate()
{
	char alphabet[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i=0;
	pointer head=(pointer)malloc(sizeof(Element));
	head->value=*(alphabet+(i++));
	pointer now=head;
	pointer new_=NULL;
	for (;*(alphabet+i)!='\0';i++)
	{
		new_=(pointer)malloc(sizeof(Element));
		new_->value=*(alphabet+i);
		now->next=new_;
		new_->prior=now;
		now=new_;
    }
    now->next=head;
    head->prior=now;
    return head;
}

void show(int skip, pointer head)
{
	pointer temp=NULL;
	if(skip>=0)
	{
		while(skip>0)
		{
			head=head->next;
			skip--;
		}
	}
	else
	{
		skip=skip*-1;
		while(skip>0)
		{
			head=head->prior;
			skip--;
		}
	}
	temp=head;
	do
	{
		printf("%c ",temp->value);
		temp=temp->next;
	}while(temp!=head);
	printf("\n\n");
}

char get_char(int loc, int skip, pointer head)
{
	while(loc>0)
	{
		head=head->next;
		loc--;
	}
	if(skip>=0)
	{
		while(skip>0)
		{
			head=head->next;
			skip--;
		}
	}
	else
	{
		skip=skip*-1;
		while(skip>0)
		{
			head=head->prior;
			skip--;
		}
	}
	return head->value;
	
}

Vigenere generate_Vigenere_couple(char *str)
{
	time_t t;
	time(&t);
	srand((unsigned int)t);
	Vigenere char_code;
	for(int i=0;;i++)
	{
		char_code.str[i]=str[i];
		char_code.code[i]=rand()% 100;
		if(str[i]=='\0')
		{
			break;
		}
	}

	return char_code;
}

void get_str_coded(char *str_coded, Vigenere char_code,pointer head) 
{
	int i;
	for (i=0;char_code.str[i]!='\0';i++)
	{
		str_coded[i]=get_char((int)(char_code.str[i]-'A'),char_code.code[i],head);
	}
	str_coded[i]='\0';
}

void get_str_decoded(char *str_decoded, char *str_coded, Vigenere char_code,pointer head)
{
	int i;
	for(i=0;str_coded[i]!='\0';i++)
	{
		str_decoded[i]=get_char((int)(str_coded[i]-'A'),-1*char_code.code[i],head);
	}
	str_decoded[i]='\0';
}


int main(void)
{
	pointer head=generate();
	/*
	show(3,head);
	show(-3,head);*/
	
	char str[MAX];
	char str_coded[MAX];
	char str_decoded[MAX];
	
	printf("enter the string you want to code!!:\n\t");
    fgets(str,MAX,stdin);str[strlen(str)-1]='\0';
    //check format
    for(int i=0;str[i]!='\0';i++)
    {
    	if(str[i]<41 || str[i]>90)
    	{
    		printf("The string should only contain Uppercase Alphabet!!\n");
    		exit(0);
		}
	}
    printf("You have enter:%s\n",str);
    
    printf("-----------------------code with Vigenere code------------------------\n");
    
    Vigenere char_code=generate_Vigenere_couple(str);
    
    printf("character-code\n");
    for (int i=0;char_code.str[i]!='\0';i++)
    {
    	printf("%c-%d\n",char_code.str[i],char_code.code[i]);
	}
	printf("\n\n");
	
	get_str_coded(str_coded,char_code,head);
	get_str_decoded(str_decoded,str_coded,char_code,head);
	printf("original:%s\n",str);
	printf("coded   :%s\n",str_coded);
	printf("decoded :%s\n",str_decoded);
	
    
    
    
	
	return 0;
 } 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
