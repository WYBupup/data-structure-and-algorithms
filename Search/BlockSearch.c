#include<stdio.h>
#include<stdlib.h>
//implement block search 
//assume that the table and the data is already established
typedef int Elemtype;

//data link
typedef struct Data_Node
{
    Elemtype data;
    struct Data_Node *next;
}Data_Node,*P_Data_Node;

//table
typedef struct Table_Node
{
    int key;//store the biggest data in the block
    P_Data_Node p;
    struct Table_Node *next; 
}Table_Node,*P_Table_Node;

P_Data_Node BlockSearch(P_Table_Node table,int key)
{
    while(table->key>=key)
    {
        table=table->next;
    }
    if(table==NULL)
    {
        return NULL;// biggest value of the data base is small than the under search data
    }
    P_Data_Node temp=table->p;
    while(temp!=NULL && temp->data<=table->key)
    {
        if(temp->data==key)
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;// there is no such data in corresponding block
}
