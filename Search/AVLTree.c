#include<stdio.h>
#include<stdlib.h>
#define LH 1
#define EH 0
#define RH -1
#define TRUE 1
#define FALSE 0
//implement AVL Tree 
typedef int Elemtype;
typedef struct AVL_Node
{
    Elemtype data;
    int balance_coeff;//LH EH RH
    struct AVL_Node *lchild,*rchild;
}AVL_Node, *AVL_tree;
 

int insert_AVL(AVL_tree *tree, Elemtype data, int *taller);
void Balance_Left(AVL_tree *tree);
void Balance_Right(AVL_tree *tree);
void FrontTranverse(AVL_tree tree); 
void init_AVL(Elemtype *array, int length,AVL_tree *tree);

int insert_AVL(AVL_tree *tree, Elemtype data, int *taller)
{
    //if successifully insert return TRUE else return FALSE
    //taller:tell if the insert result for height increase
    if(!*tree)
    {
        //the inserted data is not in the tree
        *tree=(AVL_tree)malloc(sizeof(AVL_Node));
        (*tree)->data=data;
        (*tree)->balance_coeff=EH;
        (*tree)->lchild=NULL;
        (*tree)->rchild=NULL;
        *taller=TRUE;
        return TRUE;
    }
    else
    {
        //find the inserted node if in the tree
        if((*tree)->data==data)
        {
            printf("%d is already in the AVL_TREE!\n");
            *taller=FALSE;
            return FALSE;
        }
        else if((*tree)->data>data)
        {
            if(!insert_AVL(&((*tree)->lchild),data,taller))
            {
                return FALSE;
            }
            if(*taller)
            {
                switch ((*tree)->balance_coeff)
                {
                case LH:
                    {
                        Balance_Left(tree);
                        *taller=FALSE;
                        break;
                    }
                case EH:
                    {
                        (*tree)->balance_coeff=LH;
                        *taller=TRUE;
                        break;
                    }
                case RH:
                    {
                        (*tree)->balance_coeff=EH;
                        *taller=FALSE;
                        break;
                    }
                default:
                    {
                        printf("error code of balance coefficient!\n");
                        exit(0);
                        break;
                    }
                }
            }
        }
        else
        {
            if(!insert_AVL(&(*tree)->rchild,data,taller))
            {
                return FALSE;
            }
            if(*taller)
            {
                switch((*tree)->balance_coeff)
                {
                    case LH:
                        {
                            (*tree)->balance_coeff=EH;
                            *taller=FALSE;
                            break;
                        }
                    case EH:
                        {
                            (*tree)->balance_coeff=RH;
                            *taller=TRUE;
                            break;
                        }
                    case RH:
                        {
                            Balance_Right(tree);
                            *taller=FALSE;
                            break;
                        }
                    default:
                        {
                            printf("error code of balance code!\n");
                            exit(0);
                            break;
                        }
                }
            }

        }
    }
}

void Balance_Left(AVL_tree *tree)
{
    //two situation LeftLeft or LeftRight
    AVL_tree p_root,p_left;
    if((*tree)->lchild->balance_coeff==RH)
    {
        p_root=*tree;
        p_left=p_root->lchild;
        AVL_tree p_left_right=p_left->rchild;
        if(!p_root || !p_left||!p_left_right)
        {
            printf("Pointer is NULL!\n");
            exit(0);
        }
        //core 
        *tree=p_left_right;
        p_left->rchild=p_left_right->lchild;
        p_root->lchild=p_left_right->rchild;
        p_left_right->lchild=p_left;
        p_left_right->rchild=p_root;
        //assign balance coefficient
        switch(p_left_right->balance_coeff)
        {
            case LH:
            {
                p_left->balance_coeff=EH;
                p_root->balance_coeff=RH;
                break;
            }
            case EH:
            {
                p_left->balance_coeff=EH;
                p_root->balance_coeff=EH;
                break;
            }
            case RH:
            {
                p_left->balance_coeff=LH;
                p_root->balance_coeff=EH;
                break;
            }
            default:
            {
                printf("when assign balance coefficient, error code of balance coefficient!\n");
                exit(0);
                break;
            }
        }
        p_left_right->balance_coeff=EH;
    }
    else
    {
        p_root=*tree;
        p_left=(*tree)->lchild;
        *tree=p_left;
        p_root->lchild=p_left->rchild;
        p_left->rchild=p_root;
        //assign balance coefficient
        p_root->balance_coeff=EH;
        p_left->balance_coeff=EH;
    }

}

void Balance_Right(AVL_tree *tree)
{
    //two situation RIGHTRIGHT or RIGHTLEFT
    AVL_tree p_root,p_right;
    if((*tree)->rchild->balance_coeff==LH)
    {   
        p_root=*tree;
        p_right=p_root->rchild;
        AVL_tree p_right_left=p_right->lchild;
        if(!p_root||!p_right_left||!p_right_left)
        {
            printf("Pointer is NULL!\n");
            exit(0);
        }
        //core 
        *tree=p_right_left;
        p_root->rchild=p_right_left->lchild;
        p_right->lchild=p_right_left->rchild;
        p_right_left->lchild=p_root;
        p_right_left->rchild=p_right;
        //assign balance coefficient
        switch(p_right_left->balance_coeff)
        {
            case LH:
            {
                p_right->balance_coeff=RH;
                p_root->balance_coeff=EH;
                break;
            }
            case EH:
            {
                p_right->balance_coeff=EH;
                p_root->balance_coeff=EH;
                break;
            }
            case RH:
            {
                p_right->balance_coeff=EH;
                p_root->balance_coeff=LH;
                break;
            }
            default:
            {
                printf("when assign balance coefficient, error code of balance coefficient!\n");
                exit(0);
                break;
            }
        }
        p_right_left->balance_coeff=EH;
    }
    else
    {
        p_root=*tree;
        p_right=(*tree)->rchild;
        *tree=p_right;
        p_root->rchild=p_right->lchild;
        p_right->lchild=p_root;
        //assign balance coefficient
        p_root->balance_coeff=EH;
        p_right->balance_coeff=EH;
    }

}

void FrontTranverse(AVL_tree tree)
{
    if(tree)
    {
        printf("%d ",tree->data);
        FrontTranverse(tree->lchild);
        FrontTranverse(tree->rchild);
    }
    else
    {
        printf("N ");
    }
}

void init_AVL(Elemtype *array, int length, AVL_tree *tree)
{
    int taller;
    for(int i=0;i<length;i++)
    {
        insert_AVL(tree,array[i],&taller);
        printf("after insert %d:\n",array[i]);
        FrontTranverse(*tree);
        putchar('\n');
    }
}

int main(void)
{
    int array[]={3,2,1,4,5,6,7,10,9,8};
    AVL_tree tree=NULL;
    init_AVL(array,10,&tree);
    return 1;
}