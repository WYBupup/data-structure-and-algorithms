#include<stdio.h>

void show_array(int *array, int length)
{
    for(int i=1;i<=length;i++)
    {
        printf("%d ",array[i]);
    }
    putchar('\n');
}

void adjust_BigTopBinaryTree(int *array, int index_insert_parent, int length)
{
    //Assign the biggest one among {parent, lchid, right} on the root of the child
    //if the tree's root is not the biggest one among {root, lchild, rchild}, then assign the element of root to the appropriate position in the tree.
    int parent=array[index_insert_parent];
    //adjust the complete binary tree to make it big top tree
    for(int index_son=2*index_insert_parent;index_son<=length;index_son*=2)
    {
        //find the biggest element's index between rchild and lchild
        if(index_son+1<=length && array[index_son]<array[index_son+1])
        {
            index_son=index_son+1;
        }

        if(array[index_son]<=parent)
        {
            break;
        }

        array[index_insert_parent]=array[index_son];
        index_insert_parent=index_son;
    }

    array[index_insert_parent]=parent;
}

void swap(int *array, int i, int j)
{
    int temp=array[i];
    array[i]=array[j];
    array[j]=temp;
}

void HeapSort(int *array, int length)
{
    // make the tree be the Big top Tree
    for(int i=length/2;i>=1;i--)
    {
        adjust_BigTopBinaryTree(array,i,length);
    }
    show_array(array,length);

    // exchange the root and largest position's element
    // and adjust the left tree
    for(int i=length;i>1;i--)
    {
        swap(array,1,i);
        adjust_BigTopBinaryTree(array, 1,i-1);
    }
}

int main(void)
{
    int array[]={-1,592,401,874,141,348,72,911,887,820,283,0,7};//For the target of index begining with one
    show_array(array,12);
    HeapSort(array,12);
    show_array(array,12);
    return 1;
}