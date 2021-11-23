#include<stdio.h>
#include<stdlib.h>

//implement binary sort tree or binary Search Tree
typedef int Elemtype;
typedef struct Node
{
    Elemtype data;
    struct Node *left,*right;
}Node,*BinSortTree;

void insert_BinarySortTree(BinSortTree *tree, Elemtype data);
void init_BinarySortTree(BinSortTree *tree,Elemtype *array,Elemtype length);
void FrontOrderTranverse(BinSortTree tree);
void MidOrderTranverse(BinSortTree tree);
void Search_BinarySortTree(BinSortTree tree,Elemtype data,BinSortTree *parent,BinSortTree *result);
void Delete_BinarySortTree(BinSortTree *tree,Elemtype data);


//init binary sort Tree
void insert_BinarySortTree(BinSortTree *tree, Elemtype data)
{
    BinSortTree parent=NULL,result=NULL;
    Search_BinarySortTree(*tree,data,&parent,&result);
    //only operate if the data is new to this tree
    if(!result)
    {
        BinSortTree new_tree=(BinSortTree)malloc(sizeof(Node));
        new_tree->data=data;
        new_tree->left=new_tree->right=NULL;
        if(!parent)
        {
            //empty tree
            *tree=new_tree;
        }
        else if(parent->data>data)
        {
            parent->left=new_tree;
        }
        else
        {
            parent->right=new_tree;
        }
    }
}

void init_BinarySortTree(BinSortTree *tree,Elemtype *array,int length)
{
    for(int i=0;i<length;i++)
    {
        insert_BinarySortTree(tree,array[i]);
    }

    //show the result
    MidOrderTranverse(*tree);
}

void FrontOrderTranverse(BinSortTree tree)
{
    if(tree)
    {
        printf("%d ",tree->data);
        FrontOrderTranverse(tree->left);
        FrontOrderTranverse(tree->right);
    }
    else
    {
        printf("N ");
    }
}

void MidOrderTranverse(BinSortTree tree)
{
    if(tree)
    {
        MidOrderTranverse(tree->left);
        printf("%d ",tree->data);
        MidOrderTranverse(tree->right);
    }
}

void Search_BinarySortTree(BinSortTree tree,Elemtype data,BinSortTree *parent,BinSortTree *result)
{
    //*parent point to the the parent node of the found node
    //if found *result point to the found node.else *result=NULL 
    *result=NULL;
    *parent=NULL;
    while(tree!=NULL)
    {
        if(tree->data==data)
        {
            *result=tree;
            break;
        }
        else if(tree->data>data)
        {
            *parent=tree;
            tree=tree->left;
        }
        else{
            *parent =tree;
            tree=tree->right;
        }
    }
}

void Delete_BinarySortTree(BinSortTree *tree,Elemtype data)
{
    BinSortTree parent=NULL,result=NULL;
    Search_BinarySortTree(*tree,data,&parent,&result);
    if(result)
    {
        //when the found node have no sub-tree
        if(result->left==NULL && result->right==NULL)
        {
            if(result==*tree)
            {
                *tree=NULL;
            }
            else
            {
                if(parent->data>data)
                {
                    parent->left=NULL;
                }
                else
                {
                    parent->right=NULL;
                }
            }
            free(result);
        }
        //when the found node has left tree
        else if(result->left==NULL)
        {
            if(result==*tree)
            {
                (*tree)=(*tree)->right;
            }
            else
            {
                if(parent->data>data)
                {
                    parent->left=result->right;
                }
                else
                {
                    parent->right=result->right;
                }
            }
            free(result);
        }
        //when the found tree has left tree
        else if(result->right==NULL)
        {
            if(result==*tree)
            {
                *tree=(*tree)->left;
            }
            else
            {
                if(parent->data>data)
                {
                    parent->left=result->left;
                }
                else
                {
                    parent->right=result->left;
                }
            }
            free(result);
        }
        //when the tree have both left and right tree
        else
        {
            //the under deleted node has both left tree and right tree
            BinSortTree left_biggest=result->left,left_biggest_pre=NULL;
            while(left_biggest->right!=NULL)
            {
                left_biggest_pre=left_biggest;
                left_biggest=left_biggest->right;
            }
            result->data=left_biggest->data;
            if(left_biggest_pre==NULL)
            {
                result->left=left_biggest->left;
            }
            else
            {
                left_biggest_pre->right=left_biggest->left;
            }
            free(left_biggest);
        }
    }
    else  
    {
        printf("%d is not in the tree!\n",data);
    }
} 
 
int main(void)
{
    Elemtype array[]={70,105,115,104,67,46,99,111,109};
    BinSortTree tree=NULL;
    init_BinarySortTree(&tree,array,9);
    putchar('\n'); 

    for(int i=0;i<9;i++)
    {    
        printf("delete %d:\n",array[i]);
        Delete_BinarySortTree(&tree,array[i]);
        MidOrderTranverse(tree);
        putchar('\n');
    }
    return 1;
}