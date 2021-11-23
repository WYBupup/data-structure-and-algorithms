#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define DEGREE 3
#define TRUE 1
#define FALSE 0
//implement B Tree Search Insert Delete

typedef int Elemtype;
typedef struct BTree_Node
{
  int is_leaf,num_children;
  Elemtype data[DEGREE];//should be DEGREE -1 but leave one for insert
  struct BTree_Node *children[DEGREE+1]; //should be DEGREE but leave one for insert
}BTree_Node, *BTree;

int Search_BTree(BTree tree,Elemtype key, BTree *result,int *index);
void Insert_element(BTree tree,Elemtype key, BTree lchild,BTree rchild,int pos);
int Insert_Recursion(BTree *tree, Elemtype key, int *split, int *insert_data, BTree *insert_lchild, BTree *insert_rchild,int is_root);
void Split_BTree(BTree tree, int *insert_data, BTree *insert_lchild,BTree *insert_rchild);
void Tranverse_BTree(BTree tree,int *identifier);
void Create_new_node(BTree *tree, int insert_data, BTree insert_lchild, BTree insert_rchild,int is_leaf);
void Insert_BTree(BTree *tree,Elemtype key);
void init_BTree(BTree *tree, Elemtype *array,int length);
void remove_element(BTree tree, int pos);
void borrow_from_sibling(BTree tree, int pos);
void merge(BTree tree, int i);
int Delete_Recursion(BTree tree,Elemtype key,int *underflow,int if_root);
void inspect_node(BTree tree);


void inspect_node(BTree tree)
{
  printf("{\nnum_children:%d\n",tree->num_children);
  printf("if leaf:%d\n",tree->is_leaf);
  printf("data:");
  for(int i=0;i<tree->num_children-1;i++)
  {
    printf("%d, ",tree->data[i]);
  }
  printf("\npointer:");
  for(int i=0;i<tree->num_children;i++)
  {
    printf("(");
    if(tree->children[i])
    {
      for(int j=0;j<tree->children[i]->num_children-1;j++)
      {
        printf("%d, ",tree->children[i]->data[j]);
      }
    }
    else
    {
      printf("N");
    }
    printf(") ");
  }
  printf("\n}\n");
}

void Insert_element(BTree tree,Elemtype key, BTree lchild, BTree rchild,int pos)
{
  //insert lchild in tree->children[pos]
  //insert data in tree->data[pos]
  //insert rchild in tree->children[pos+1]
  if(tree->num_children==DEGREE+1)
  {
    printf("during insert there exits node not splited!\n");
    exit(0);
  }
  //pos: the insert position posth pointer's location
  int j=tree->num_children-1;//number of keys of the node
  while(j>pos)
  {
    tree->data[j]=tree->data[j-1];
    tree->children[j+1]=tree->children[j];
    j--;
  }
  tree->children[pos]=lchild;
  tree->data[pos]=key;
  tree->children[pos+1]=rchild;
  tree->num_children++;
}

int Search_BTree(BTree tree, Elemtype key,BTree *result, int *index)
{
  //if found return the pointer to the found node and the index of the target of the data array of the node
  if(!tree)
  {
    printf("BTree is empty!\n");
    return FALSE;
  }
  if(tree->num_children<ceil(DEGREE/2)||tree->num_children>DEGREE)
  {
    printf("during search, found wrong number of node's number of children!\n");
    return FALSE;
  }
  int i=0;
  while(i<tree->num_children-1 && key>tree->data[i])
  {
    i=i+1;
  }
  //the key is in this node
  if(i<tree->num_children-1 && key==tree->data[i])
  {
    *result=tree;
    *index=i;
    return TRUE;
  }
  //the key is in the children
  if(tree->is_leaf)
  {
    printf("%d is not in the Tree!\n",key);
    return FALSE;
  }
  else
  {
    if(Search_BTree(tree->children[i],key,result,index))
    {
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
}

void Split_BTree(BTree tree, Elemtype *insert_data, BTree *insert_lchild,BTree *insert_rchild)
{
  if(tree->num_children>=ceil(DEGREE/2)&&tree->num_children<=DEGREE)
  {
    printf("split the not full node!\n");
    exit(0);
  }
  int pos=(tree->num_children-1)/2;
  //insert_data
  *insert_data=tree->data[pos];
  //insert_lchild and insert_rchild
  *insert_lchild=(BTree)malloc(sizeof(BTree_Node));
  *insert_rchild=(BTree)malloc(sizeof(BTree_Node));
  //is_leaf
  if(tree->is_leaf)
  {
    (*insert_rchild)->is_leaf=TRUE;
    (*insert_lchild)->is_leaf=TRUE;
  }
  else
  {
    (*insert_rchild)->is_leaf=FALSE;
    (*insert_lchild)->is_leaf=FALSE;
  }
  //num_children, data, children
  //lchild
  (*insert_lchild)->num_children=0;
  for(int i=0;i<pos;i++)
  {
    (*insert_lchild)->children[(*insert_lchild)->num_children]=tree->children[i];
    (*insert_lchild)->data[(*insert_lchild)->num_children]=tree->data[i];
    (*insert_lchild)->num_children++;
  }
  (*insert_lchild)->children[(*insert_lchild)->num_children]=tree->children[pos];
  (*insert_lchild)->num_children++;
  //rchild
  (*insert_rchild)->num_children=0;
  for(int i=pos+1;i<tree->num_children-1;i++)
  {
    (*insert_rchild)->children[(*insert_rchild)->num_children]=tree->children[i];
    (*insert_rchild)->data[(*insert_rchild)->num_children]=tree->data[i];
    (*insert_rchild)->num_children++;
  }
  (*insert_rchild)->children[(*insert_rchild)->num_children]=tree->children[tree->num_children-1];
  (*insert_rchild)->num_children++;
  free(tree);
  /*
  printf("split:\nleft:(");
  for(int i=0;i<(*insert_lchild)->num_children-1;i++)
  {
    printf("%d, ",(*insert_lchild)->data[i]);
  }
  printf(")   data:%d   right:(",*insert_data);
  for(int i=0;i<(*insert_rchild)->num_children-1;i++)
  {
    printf("%d, ",(*insert_rchild)->data[i]);
  }
  printf(")\n\n");
  */
}

void Create_new_node(BTree *tree, int insert_data, BTree insert_lchild, BTree insert_rchild,int is_leaf)
{
  *tree=(BTree)malloc(sizeof(BTree_Node));
  (*tree)->data[0]=insert_data;
  (*tree)->children[0]=insert_lchild;
  (*tree)->children[1]=insert_rchild;
  for(int i=2;i<DEGREE+1;i++)
  {
    (*tree)->children[i]=NULL;
  }
  (*tree)->is_leaf=is_leaf;
  (*tree)->num_children=2;
}

int Insert_Recursion(BTree *tree, Elemtype key, int *split, int *insert_data, BTree *insert_lchild, BTree *insert_rchild,int is_root)
{
  //the root is null;
  if(!*tree)
  {
    Create_new_node(tree,key,NULL,NULL,TRUE);
    *split=FALSE;
    return TRUE;
  }
  //if the B Tree is not null;
  int i=0;
  while(i<(*tree)->num_children-1 && key>(*tree)->data[i])//tell is from left to right
  {
    i++;
  }
  //key is already in the tree
  if(i<(*tree)->num_children && key==(*tree)->data[i])
  {
    printf("%d is already in the B Tree!\n");
    return FALSE;
  }
  //key is not in BTree
  //insert the data in the leaf
  if((*tree)->is_leaf)
  {
    Insert_element(*tree,key,NULL,NULL,i);
    //if the node is root node and is out of range
    if((*tree)->num_children>DEGREE)
    {
      *split=TRUE;
      //split the node in lchild, data, rchild where data is the median
      Split_BTree(*tree,insert_data,insert_lchild,insert_rchild);
      //if the tree only have one layer
      if(is_root)
      {
        Create_new_node(tree,*insert_data,*insert_lchild,*insert_rchild,FALSE);
        *split=FALSE;
      }
    }
    //if the node is in range
    else
    {
      *split=FALSE;
    }
    return TRUE;
  }
  else
  {
    if(Insert_Recursion(&(*tree)->children[i],key,split,insert_data,insert_lchild,insert_rchild,FALSE))
    {
      if(*split)
      {
        Insert_element(*tree,*insert_data,*insert_lchild,*insert_rchild,i);
        if((*tree)->num_children>DEGREE)
        {
          Split_BTree(*tree,insert_data,insert_lchild,insert_rchild);
          //if the root is full
          if(is_root)
          {
            Create_new_node(tree,*insert_data,*insert_lchild,*insert_rchild,FALSE);
            *split=FALSE;
          }
        }
        else
        {
          *split=FALSE;
        }
      }
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
}
 
void tranverse_BTree(BTree tree,int *identifier)
{
  if(tree)
  {
    (*identifier)++;
    int i,id=*identifier;
    for(i=0;i<tree->num_children-1;i++)
    {
      tranverse_BTree(tree->children[i],identifier);
      if(tree->is_leaf)
      {
        printf("(Leaf_Node");
      }
      else
      {
        printf("(Internal Node");
      }
      printf("%d,%d)  ",id,tree->data[i]);
    }
    tranverse_BTree(tree->children[tree->num_children-1],identifier);
  }
  else
  {
    printf("N ");
  }
}

void Insert_BTree(BTree *tree,Elemtype key)
{
  int insert_data,split;
  BTree insert_lchild,insert_rchild;
  Insert_Recursion(tree,key,&split,&insert_data,&insert_lchild,&insert_rchild,TRUE);
}

void init_BTree(BTree *tree, Elemtype *array,int length)
{
  int identifier;
  for(int i=0;i<length;i++)
  {
    identifier=0;
    printf("insert %d:\n",array[i]);
    Insert_BTree(tree,array[i]);
    tranverse_BTree(*tree,&identifier);
    printf("\n\n");
  }
}

void remove_element(BTree tree, int pos)
{
  //pos: the position of deleted data
  //the node should be leaf node 
  if(pos>=tree->num_children-1 || !tree->is_leaf)
  {
    printf("\nDuring delete operation: Delete index out of range of data in the node or the node is internal node!\n");
    printf("node info:\ndata:");
    for(int j=0;j<tree->num_children-1;j++)
    {
      printf("%d, ",tree->data[j]);
    }
    printf("delete pos:%d\n",pos);
    printf("if tree is leaf:%d\n",tree->is_leaf);
    printf("tree->num_children-1:%d\n",tree->num_children-1);
    exit(0);
  }
  printf("remove %d\n",tree->data[pos]);
  int j=tree->num_children-2;
  while(j>pos)
  {
    tree->data[j-1]=tree->data[j];
    j--;
  }
  tree->num_children--;
}

void borrow_from_sibling(BTree tree, int pos)
{
  //pos the children index who faces underflow problem
  BTree sibling,insert_lchild,insert_rchild;
  Elemtype middle_data;
  //the index of children in the node facing underflow problem where will be replace by children-data-children
  //the index of data in the node of sibling which will be removed
  int insert_index,delete_index;
  if(pos>0)
  {
    sibling=tree->children[pos-1];
    middle_data=tree->data[pos-1];
    insert_lchild=sibling->children[sibling->num_children-1];
    insert_rchild=tree->children[pos]->children[0];
    insert_index=0;
    delete_index=sibling->num_children-2;
  }
  else
  {
    sibling=tree->children[pos+1];
    middle_data=tree->data[pos];
    insert_lchild=tree->children[pos]->children[tree->children[pos]->num_children-1];
    insert_rchild=sibling->children[0];
    insert_index=tree->children[pos]->num_children-1;
    delete_index=0;
  }
  /*
  printf("borrow %d from sibling \n",sibling->data[delete_index]);
  printf("sibling:\n");
  printf("middle data:%d\n",middle_data);
  inspect_node(sibling);
  printf("lchild:\n");
  inspect_node(insert_lchild);
  printf("rchild:\n");
  inspect_node(insert_rchild);
  for(int k=0;k<sibling->num_children-1;k++)
  {
    printf("%d, ",sibling->data[k]);
  }
  printf("\n");*/
  Insert_element(tree->children[pos],middle_data,insert_lchild,insert_rchild,insert_index);
  tree->data[pos>0?pos-1:pos]=sibling->data[delete_index];
  //delete element in the sibling
  if(pos==0)
  {
    for(int j=0;j<sibling->num_children-2;j++)
    {
      sibling->children[j]=sibling->children[j+1];
      sibling->data[j]=sibling->data[j+1];
    }
    sibling->children[sibling->num_children-2]=sibling->children[sibling->num_children-1];
  }
  sibling->children[sibling->num_children-1]=NULL;
  sibling->num_children--;
  /*
  printf("result of parent node after borrowing:\n");
  inspect_node(tree);
  */
}

void merge(BTree tree, int i)
{
  //i the index of the children in tree who faces underflow problem
  //merge
  BTree left_child,right_child,sibling;
  Elemtype middle_data;
  int exchange_index;//the index of the children should be replaced by the generated merge children
  if(i>0)
  {
    sibling=tree->children[i-1];
    middle_data=tree->data[i-1];
    left_child=sibling;
    right_child=tree->children[i];
    exchange_index=i-1;
  }
  else
  {
    sibling=tree->children[i+1];
    middle_data=tree->data[i];
    left_child=tree->children[i];
    right_child=sibling;
    exchange_index=i;
  }
  //printf("merge: left(");
  BTree new_=(BTree)malloc(sizeof(BTree_Node));
  new_->is_leaf=sibling->is_leaf;
  new_->num_children=0;
  for(int j=0;j<left_child->num_children-1;j++)
  {
    new_->children[new_->num_children]=left_child->children[j];
    new_->data[new_->num_children]=left_child->data[j];
    new_->num_children++;
    //printf("%d, ",left_child->data[j]);
  }
  new_->children[new_->num_children]=left_child->children[left_child->num_children-1];
  new_->data[new_->num_children]=middle_data;
  new_->num_children++;
  //printf(") middle:(%d) right(",middle_data);
  for(int j=0;j<right_child->num_children-1;j++)
  {
    new_->children[new_->num_children]=right_child->children[j];
    new_->data[new_->num_children]=right_child->data[j];
    new_->num_children++;
    //printf("%d, ",right_child->data[j]);
  }
  //printf(")\n");
  new_->children[new_->num_children]=right_child->children[right_child->num_children-1];
  new_->num_children++;
  free(left_child);
  free(right_child);
  tree->children[exchange_index]=new_;
  /*
  printf("new node:");
  for(int j=0;j<new_->num_children-1;j++)
  {
    printf("%d, ",new_->data[j]);
  }
  printf("\n");
  */
  for(int j=exchange_index;j<tree->num_children-2;j++)
  {
    tree->data[j]=tree->data[j+1];
    tree->children[j+1]=tree->children[j+2];
  }
  tree->num_children--;
  /*
  printf("after merge the parent node:\n");
  inspect_node(tree);*/
}

int Delete_Recursion(BTree tree,Elemtype key,int *underflow,int if_root)
{
  //the tree is empty
  if(!tree)
  {
    printf("the BTree is empty!\n");
    return FALSE;
  }

  //search the key
  int i=0;
  while(i<tree->num_children-1 && key>tree->data[i])
  {
    i++;
  }

  //if the key is in this node
  if(i<tree->num_children-1 && key==tree->data[i])
  {
    //if the node is internal node 
    if(!tree->is_leaf)
    {
      //found its inorder predecessor and exchange the value and delete that element in the leaf node
      Elemtype inorder_predecessor;
      BTree temp=tree->children[i];
      while(!temp->is_leaf)
      {
        temp=temp->children[temp->num_children-1];
      }
      inorder_predecessor=temp->data[temp->num_children-2];
      tree->data[i]=inorder_predecessor;
      Delete_Recursion(tree->children[i],inorder_predecessor,underflow,FALSE);//must return TRUE
      goto label;
    }
    //if the node is leaf node
    else
    {
      //delete the data
      remove_element(tree,i);
      //if underflow occurs
      if(!if_root&&tree->num_children<ceil(DEGREE/2.))
      {
        *underflow=TRUE;
      }
      //if underflow does not occur
      else
      {
        *underflow=FALSE;
      }
    }
    return TRUE;
  }
  //if the key is not in the node
  //the key is not in the tree
  if(tree->is_leaf)
  {
    printf("%d is not in the BTree!\n",key);
    return FALSE;
  }
  //recurse to search the key
  else
  {
    if(Delete_Recursion(tree->children[i],key,underflow,FALSE))
    {
label:
      //if the children node occurs underflow
      if(*underflow)
      {
        //found if its immediate left sibling or right sibling has extra data
        //if the sibling has extra data
        if(tree->children[i>0?i-1:i+1]->num_children>ceil(DEGREE/2.))
        {
          borrow_from_sibling(tree,i);
          *underflow=FALSE;
        }
        //if the sibling have no extra data to use
        else
        {
          //merge
          merge(tree,i);
          if(if_root || tree->num_children>=ceil(DEGREE/2.))
          {
            *underflow=FALSE;
          }
        }
      }
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
}

void Delete_BTree(BTree tree,Elemtype key)
{ 
  int under_flow,identifier=0;
  printf("delete %d:\n",key);
  Delete_Recursion(tree,key,&under_flow,TRUE);
  tranverse_BTree(tree,&identifier);
  printf("\n\n");
}

int main(void) 
{
  int array[]={8,9,10,11,15,16,17,18,20,23};
  //init
  BTree tree=NULL;
  init_BTree(&tree,array,10);

  Delete_BTree(tree,100);
  
  return 1;
}