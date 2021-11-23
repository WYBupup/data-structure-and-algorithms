#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define HASHSIZE 128
#define P 127

//implement Hash search 
//hash fuction: 除留余数法
//conflict deal function: 溢出区法
typedef struct 
{
    int key;
}Elemtype;

typedef struct
{
    int *flag_hashtable;//tell if hashtable's corresponding position is occupied
    int hashtable_count,conflicttable_count;
    int conflicttable_size;
    Elemtype *hash_table;
    Elemtype *conflict_table;
}HashTable;

void init_HashTable(HashTable *hashtable);
void update_ConflictTable(HashTable *hashtable);
int Search_DivideAndLeaveReminder(HashTable *hashtable,int key);
int FindConflictTable(Elemtype *conflict_table,int key,int conflict_table_length,Elemtype *result);
void Insert(HashTable *hashtable, Elemtype data);
int FindLargestPrime(int hashtable_size);
int if_Prime(int number);

void init_HashTable(HashTable *hashtable)
{
    hashtable->conflicttable_size=HASHSIZE;
    hashtable->conflict_table=(Elemtype *)malloc(sizeof(Elemtype)*hashtable->conflicttable_size);
    if(hashtable->conflict_table==NULL)
    {
        printf("Fail to allocate memory!\n");
        exit(0);
    }
    hashtable->hash_table=(Elemtype *)malloc(sizeof(Elemtype)*HASHSIZE);
    if(hashtable->hash_table==NULL)
    {
        printf("Fail to allocate memory!\n");
        exit(0);
    }
    hashtable->conflicttable_count=0;
    hashtable->hashtable_count=0;
    hashtable->flag_hashtable=(int *)malloc(sizeof(int)*HASHSIZE);
    if(hashtable->flag_hashtable==NULL)
    {
        printf("Fail to allocate memory!\n");
        exit(0);
    }
    for(int i=0;i<HASHSIZE;i++)
    {
        hashtable->flag_hashtable[i]=0;
    }
}

void update_ConflictTable(HashTable *hashtable)
{
    hashtable->conflicttable_size=hashtable->conflicttable_size+HASHSIZE;
    hashtable->conflict_table=(Elemtype *)realloc(hashtable->conflict_table,sizeof(Elemtype)*hashtable->conflicttable_size);
    if(hashtable->conflict_table==NULL)
    {
        printf("Fail to allocate memory!\n");
        exit(0);
    }
}

int FindConflictTable(Elemtype *conflict_table,int key,int conflicttable_count,Elemtype *result)
{
    for(int i=0;i<conflicttable_count;i++)
    {
        if(conflict_table[i].key==key)
        {
            *result=conflict_table[i];
            return TRUE;
        }
    }
    return FALSE;
}

int Search_DivideAndLeaveReminder(HashTable *hashtable,int key, Elemtype *result)
{
    int index=key%P;
    if(hashtable->flag_hashtable[index]!=1)
    {
        printf("error corresponding position is empty!\n");
        return FALSE;
    }
    if(hashtable->hash_table[index].key==key)
    {
        *result=hashtable->hash_table[index];
    }
    else
    {
        if(FindConflictTable(hashtable->conflict_table,key,hashtable->conflicttable_count,result))
        {
            return TRUE;
        }
        else
        {
            printf("element whose key is %d is not in the hash table!\n");
            return FALSE;
        }
    }
}

void Insert(HashTable *hashtable, Elemtype data)
{
    int index=data.key%P;
    if(!hashtable->flag_hashtable[index])
    {
        hashtable->hash_table[index]=data;
        hashtable->hashtable_count++;
    }
    else
    {
        if(hashtable->conflicttable_count>=hashtable->conflicttable_size)
        {
            update_ConflictTable(hashtable);
        }
        hashtable->conflict_table[hashtable->conflicttable_count]=data;
        hashtable->conflicttable_count++;
    }

}

int FindLargestPrime(int hashtable_size)
{
    if(hashtable_size<=0)
    {
        printf("number should be bigger than zero!\n");
        return -1;
    }
    while(!if_prime(hashtable_size))
    {
        hashtable_size--;
    }
    return hashtable_size;
}

int if_Prime(int number)
{
    for(int i=2;i<=number/2;i++)//number=4 i=2
    {
        if(number%i==0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

int main(void)
{
    return 1;
}